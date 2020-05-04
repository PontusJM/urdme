/* urdmerng.c - URDME random number generators */

/* P. Melin 2020-04-09 */

#include <stdlib.h>
#include "mex.h"
#include "urdmerng.h"
#include <gsl/gsl_rng.h>

rand_state_t *init_rng(){
  rand_state_t *rng = (rand_state_t *)MALLOC(sizeof(rand_state_t));
  switch(URDMERNG){
  case GSL:
    ;
    gsl_rng *gsl = gsl_rng_alloc (gsl_rng_taus);
    rng->gsl = gsl;
    return rng;
  default:
    ;
    unsigned int *sd = (unsigned int *)MALLOC(sizeof(unsigned int));
    rng->state = sd;
    return rng;
  }
}

void destroy_rng(rand_state_t *rng){
  switch(URDMERNG){
  case GSL:
    gsl_rng_free(rng->gsl);
    break;
  default:
    break;
  }
  FREE(rng);
}

void seed_rng(rand_state_t *rng, unsigned int seed){
  switch(URDMERNG){
  case GSL:
    gsl_rng_set(rng->gsl,seed);
    break;
  case DRAND48:
    srand48(seed);
    break;
  default:
    *(rng->state) = seed;
    break;
  }
}

