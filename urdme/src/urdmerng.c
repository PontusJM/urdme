/* urdmerng.c - URDME random number generators */

/* P. Melin 2020-04-09 */

#include <stdlib.h>
#include "mex.h"
#include "urdmerng.h"
#include <gsl/gsl_rng.h>

rand_state_t *init_rng(){
  rand_state_t *rng = (rand_state_t *)MALLOC(sizeof(rand_state_t));
  if(URDMERNG >= 3 && URDMERNG <= 7){
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
    case GSL_RANLXS1:
      gsl = gsl_rng_alloc (gsl_rng_ranlxs1);
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
    unsigned int *sd = (unsigned int *)MALLOC(sizeof(unsigned int));
    rng->state = sd;
    return rng;
  }
}

void destroy_rng(rand_state_t *rng){
  if(URDMERNG >= 3 && URDMERNG <= 7){
    gsl_rng_free(rng->gsl);
  }
  FREE(rng);
}

void seed_rng(rand_state_t *rng, unsigned int seed){
  if(URDMERNG >= 3 && URDMERNG <= 7){
    gsl_rng_set(rng->gsl,seed);
  }else if(URDMERNG == 2){
    srand48(seed);
  }else{
    *(rng->state) = seed;
  }
}
