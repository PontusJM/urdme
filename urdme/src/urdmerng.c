/* urdmerng.c - URDME random number generators */

/* P. Melin 2020-05-19 */

#include <stdlib.h>
#include "mex.h"
#include "urdmerng.h"
#include <gsl/gsl_rng.h>

rand_state_t *init_rng(){
  rand_state_t *rng = (rand_state_t *)MALLOC(sizeof(rand_state_t));
  if(URDMERNG >= 3 && URDMERNG <= 6){
    gsl_rng *gsl;
    switch(URDMERNG){
    case GSL_TAUS2:
      gsl = gsl_rng_alloc (gsl_rng_taus2);
      break;
    case GSL_MT19937:
      gsl = gsl_rng_alloc (gsl_rng_mt19937);
      break;
    case GSL_RANLXS0:
      gsl = gsl_rng_alloc (gsl_rng_ranlxs0);
      break;
    case GSL_RANLXS2:
      gsl = gsl_rng_alloc (gsl_rng_ranlxs2);
      break;
    default:
      break;
    }
    rng->gsl = gsl;
    return rng;
  }else{
    rng->state = (unsigned int *)MALLOC(sizeof(unsigned int));
    return rng;
  }
}
