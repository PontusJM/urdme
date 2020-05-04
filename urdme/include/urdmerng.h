/* urdmerng.h - URDME random number generators */

/* P. Melin 2020-04-09 */

#include <gsl/gsl_rng.h>


typedef union rand_state_t{
  unsigned int *state;
  gsl_rng *gsl;
} rand_state_t;

/* rng codes */
#define RAND_R 1
#define DRAND48 2
#define GSL 3

/* select sampling function at compile time 
   default to drand48() */
#if URDMERNG == 1
#define sample_rng(rng) ((double) rand_r(rng->state) / (double) RAND_MAX)
#elif URMDERNG == 2
#define sample_rng(rng) (double) drand48()
#elif URDMERNG == 3
#define sample_rng(rng) (double) gsl_rng_uniform(rng->gsl)
#else
#define sample_rng(rng) drand48()
#endif

/* Initializes a random number generator with seed */
rand_state_t *init_rng();

/* Destroys a random number generator */
void destroy_rng(rand_state_t *rng);

void seed_rng(rand_state_t *rng, unsigned int seed);

