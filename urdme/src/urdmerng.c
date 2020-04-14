/* urdmerng.c - URDME random number generators */

/* P. Melin 2020-04-09 */

#include <stdlib.h>
#include "urdmerng.h"

rand_state_t *init_rng(unsigned int seed){
  rand_state_t *rng = (rand_state_t *)malloc(sizeof(rand_state_t));
  *rng = seed;
  return rng;
}

void destroy_rng(rand_state_t *rng){
  free(rng);
}
