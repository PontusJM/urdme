/* ssa.c - URDME SSA solver. */

/* P. Melin   2020-04-08 (OpenMP support urdmerng integration) */
/* S. Engblom 2019-11-15 (Nreplicas, multiple seeds syntax) */
/* S. Engblom 2017-02-22 */

#include <string.h>
#include <math.h>
#include <omp.h>
#include <gsl/gsl_rng.h>

#include "propensities.h"
#include "inline.h"
#include "report.h"
#include "ssa.h"
#include "urdmerng.h"

#if !defined(MALLOC) || !defined(FREE)
  #error "Must define MALLOC and FREE."
#endif

/*----------------------------------------------------------------------*/
void ssa(const PropensityFun *rfun, 
	 const int *u0,
	 const size_t *irN,const size_t *jcN,const int *prN,
	 const size_t *irG,const size_t *jcG,
	 const double *tspan,const size_t tlen,const size_t Nreplicas,
	 int *U,
	 const double *vol,const double *ldata,const double *gdata,
	 const int *sd,
	 const size_t Ncells,
	 const size_t Mspecies,const size_t Mreactions,
	 const size_t dsize,
	 int report_level,const long *seed_long,
	 const double *K,const int *I,
	 const size_t *jcS,const int *prS,const size_t M1,
	 int threads
	 )

/* Specification of the inputs, see nsm.c */
{
  /* stats */
  long int total_reactions = 0;
  int errcode = 0;
  const int event = -1; /* only reactions are handled by SSA */
  const size_t Ndofs = Ncells*Mspecies;
  
  /* reporter */
  ReportFun report = &URDMEreportFun;
  
  /* OpenMP */
  #if defined(_OPENMP)
  omp_set_num_threads(threads);
  rand_state_t *rngs[threads];
  for (int n = 0; n < threads; n++){
    rngs[n] = init_rng();
  }
  #endif
  
  /* Loop over Nreplicas cases. */
  for (int k = 0; k < Nreplicas; k++) {
    
    /* Seed the rngs accordingly, unique seed for each rng */
    for(int i = 0; i < threads; i++){
      rng_seed(rngs[i],seed_long[k]+i);
    }
    
    /* main loop over the (independent) cells */ 
    #pragma omp parallel for
    for (size_t subvol = 0; subvol < Ncells; subvol++) {
      
      /* Determine which rng to use */
      rand_state_t *rng = rngs[omp_get_thread_num()];
      
      size_t it = 0;
      double tt = tspan[0];

      /* allocate state vector */
      int *xx = (int *)MALLOC(Mspecies*sizeof(int));

      /* allocate reaction rate vector */
      double *rrate = (double *)MALLOC(Mreactions*sizeof(double));

      /* sum of reaction rates */
      double srrate;
      
      /* Set (xx,tt) to the initial state. */
      memcpy(xx,&u0[Mspecies*subvol+k*Ndofs],Mspecies*sizeof(int));
      
      /* Calculate the propensity for every reaction. Store the sum of
	 the reaction intensities in srrate. */
      size_t j;
      srrate = 0.0;
      for (j = 0; j < M1; j++) {
	double temp = inlineProp(xx,&K[j*3],&I[j*3],&prS[jcS[j]],
			      jcS[j+1]-jcS[j],vol[subvol],sd[subvol]);
	rrate[j] = temp;
	srrate += rrate[j];
      }
      for (; j < Mreactions; j++) {
	double temp =  (*rfun[j-M1])(xx,tt,vol[subvol],
				 &ldata[subvol*dsize],gdata,sd[subvol]);
	rrate[j] = temp;
	srrate += rrate[j];
      }
      
      /* Main simulation loop. */
      for ( ; ; ) {
	/* time for next reaction */
	tt -= log(1.0-sample_rng(rng))/srrate;
	//tt -= log(1.0-((double) rand_r(&seed)/ (double) RAND_MAX))/srrate;
	
	/* Store solution if the global time counter tt has passed the
	   next time in tspan. */
	if (tt >= tspan[it] || isinf(tt)) {
	  for (; it < tlen && (tt >= tspan[it] || isinf(tt)); it++)
	    memcpy(&U[k*Ndofs*tlen+Mspecies*subvol+Ndofs*it],xx,Mspecies*sizeof(int));
	  
	  /* If the simulation has reached the final time, continue to
	     next subvolume. */
	  if (it >= tlen) break;
	}
	
	/* a) Determine the reaction re that did occur. */
	const double rand = sample_rng(rng)*srrate;
	double cum;
	int re;
	for (re = 0, cum = rrate[0]; re < Mreactions && rand > cum;
	     cum += rrate[++re]);
	
	/* elaborate floating point fix: */
	if (re >= Mreactions) re = Mreactions-1;
	if (rrate[re] == 0.0) {
	  /* go backwards and try to find first nonzero reaction rate */
	  for ( ; re > 0 && rrate[re] == 0.0; re--);
	  
	  /* No nonzero rate found, but a reaction was sampled. This can
	     happen due to floating point errors in the iterated
	     recalculated rates. */
	  if (rrate[re] == 0.0) {
	    /* nil event: zero out and move on */
	    srrate = 0.0;
	    goto next_event;
	  }
	}

	/* b) Update the state of the subvolume. */
	for (int i = jcN[re]; i < jcN[re+1]; i++) {
	  xx[irN[i]] += prN[i];
	  if (xx[irN[i]] < 0) errcode = 1;
	}

	/* c) Recalculate srrate and rrate using dependency graph. */
	for (int i = jcG[Mspecies+re]; i < jcG[Mspecies+re+1]; i++) {
	  const int j = irG[i];
	  const double old = rrate[j];
	  if (j < M1){
	    rrate[j] = inlineProp(xx,&K[j*3],&I[j*3],&prS[jcS[j]], jcS[j+1]-jcS[j],vol[subvol],sd[subvol]);
	    srrate += rrate[j]-old;
	  }
	  else{
	    rrate[j] = (*rfun[j-M1])(xx,tt,vol[subvol], &ldata[subvol*dsize], gdata,sd[subvol]);
	    srrate += rrate[j]-old;
	  }
	}
	
	total_reactions++; /* counter */

      next_event:
	/* Check for error codes. */
	if (errcode) {
	  /* Report the error that occurred and exit. */
	  memcpy(&U[k*Ndofs*tlen+Mspecies*subvol+Ndofs*it],xx,Mspecies*sizeof(int));
	  //report(k*Ncells+subvol,0,Nreplicas*Ncells,
	  //	 0,total_reactions,errcode,report_level);
	  break;
	}
      }
      if (report_level)
	;
	//report(k*Ncells+subvol,0,Nreplicas*Ncells,
	//	       0,total_reactions,0,report_level);
      FREE(rrate);
      FREE(xx);
    }
  }
  /* Destroy the allocated rngs */
  for(int i = 0; i < threads; i++){
    destroy_rng(rngs[i]);
  }
}
/*----------------------------------------------------------------------*/
