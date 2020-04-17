/* urdmerng.c - URDME random number generators */

/* P. Melin 2020-04-09 */

#include <stdlib.h>
#include "mex.h"
#include "urdmerng.h"
#include <gsl/gsl_rng.h>

rand_state_t *init_rng(unsigned int seed){
  rand_state_t *state = (rand_state_t *)MALLOC(sizeof(rand_state_t));
  *state = seed;
  return state;
}

void destroy_rng(rand_state_t *rng){
  FREE(rng);
}
