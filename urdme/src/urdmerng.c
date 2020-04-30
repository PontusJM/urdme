/* urdmerng.c - URDME random number generators */

/* P. Melin 2020-04-09 */

#include <stdlib.h>
#include "mex.h"
#include "urdmerng.h"
#include <gsl/gsl_rng.h>

rand_state_t *init_rng(int Nreplicas){
  rand_state_t *rng = (rand_state_t *)MALLOC(sizeof(rand_state_t));
  state_t *states = (state_t *)MALLOC(sizeof(state_t)*Nreplicas);
  rng->states = states;
  rng->replicas = Nreplicas;
  for(int i = 0; i < rng->replicas; i++){
  switch(URDMERNG){
  case GSL:
    ;
    gsl_rng *gsl = gsl_rng_alloc (gsl_rng_taus);
    rng->states[i].ptr.gsl = gsl;
    rng->states[i].initialized = false;
  default:
    ;
    unsigned int *sd = (unsigned int *)MALLOC(sizeof(unsigned int));
    rng->states[i].ptr.state = sd;
    rng->states[i].initialized = false;
  }
  }
  return rng;
}

void destroy_rng(rand_state_t *rng){
  switch(URDMERNG){
  case GSL:
    for(int i = 0; i < rng->replicas; i++){
      gsl_rng_free(rng->states[i].ptr.gsl);
    }
    break;
  default:
    break;
  }
  FREE(rng);
}

void seed_rng(rand_state_t *rng, unsigned int seed, int replica){
  switch(URDMERNG){
  case GSL:
    gsl_rng_set(rng->states[replica].ptr.gsl,seed);
    break;
  case DRAND48:
    srand48(seed);
    break;
  default:
    *(rng->states[replica].ptr.state) = seed;
    break;
  }
  if(!rng->states[replica].initialized) rng->states[replica].initialized = true;
}

bool is_initialized(rand_state_t *rng,int replica){
  switch(URDMERNG){
  default:
    return rng->states[replica].initialized;
  }
}
