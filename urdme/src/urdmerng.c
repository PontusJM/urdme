/* urdmerng.c - URDME random number generators */

/* P. Melin 2020-04-09 */

#include <stdlib.h>
#include "urdmerng.h"

rng_t *init_rng(RngType type, unsigned int seed){
  rng_t *rng = malloc(sizeof(rng_t));
  rng->type = type;
  rng->state = seed;
  switch (type)
    {
    case DRAND48:
      srand48(seed);
      return rng;
    default:
      return rng;
    }
}

void destroy_rng(rng_t *rng){
  switch(rng->type)
    {
    default:
      free(rng);
      break;
    }
}

double rand_sample(rng_t *rng){
  switch(rng->type)
    {
    case RAND_R:
      return ((double) rand_r(&(rng->state)) / (double) RAND_MAX);
    case DRAND48:
      return drand48();
    default:
      return -1;
    }
}
  
