/* urdmerng.h - URDME random number generators */

/* P. Melin 2020-05-19 */

#include <gsl/gsl_rng.h>

typedef union rand_state_t{
  unsigned int *state;
  gsl_rng *gsl;
} rand_state_t;

/* rng codes */
#define RAND_R 1
#define DRAND48 2
#define GSL_TAUS2 3
#define GSL_MT19937 4
#define GSL_RANLXS0 5
#define GSL_RANLXS2 6


/* select seeding, sampling and destruction behaviours at compile time */
#if URDMERNG == 1 /* RAND_R */
#define seed_rng(rng,seed) *(rng->state) = seed
#define sample_rng(rng) ((double) rand_r(rng->state) / (double) RAND_MAX)
#define destroy_rng(rng) FREE(rng)
#elif URMDERNG == 2 /* DRAND48 */
#define seed_rng(rng,seed) srand48(seed)
#define sample_rng(rng) (double) drand48()
#define destroy_rng(rng) FREE(rng)
#elif URDMERNG >= 3 && URDMERNG <= 6 /* GSL */
#define seed_rng(rng,seed) gsl_rng_set(rng->gsl,seed)
#define sample_rng(rng) (double) gsl_rng_uniform(rng->gsl)
#define destroy_rng(rng) gsl_rng_free(rng->gsl); FREE(rng)
#else /* DEFAULT */
#define seed_rng(rng,seed) srand48(seed)
#define sample_rng(rng) drand48()
#define destroy_rng(rng) FREE(rng)
#endif

/* Initializes a random number generator */
rand_state_t *init_rng();
