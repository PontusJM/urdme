/* urdmerng.h - URDME random number generators */

/* P. Melin 2020-04-09 */

#include <gsl/gsl_rng.h>


typedef union state_ptr{
  unsigned int *state;
  gsl_rng *gsl;
} state_ptr;

typedef struct {
  state_ptr ptr;
  bool initialized;
} state_t;

typedef struct {
  int replicas;
  state_t *states;
} rand_state_t;

/* rng codes */
#define RAND_R 1
#define DRAND48 2
#define GSL 3

/* select sampling function at compile time 
   default to drand48() */
#if URDMERNG == 1
#define sample_rng(rng,k) ((double) rand_r(rng->states[k].ptr.state) / (double) RAND_MAX)
#elif URMDERNG == 2
#define sample_rng(rng,k) (double) drand48()
#elif URDMERNG == 3
#define sample_rng(rng,k) gsl_rng_uniform(rng->states[k].ptr.gsl)
#else
#define sample_rng(rng,k) -1
#endif

/* Initializes a random number generator with seed */
rand_state_t *init_rng();

/* Destroys a random number generator */
void destroy_rng(rand_state_t *rng);

void seed_rng(rand_state_t *rng, unsigned int seed, int replica);

bool is_initialized(rand_state_t *rng, int replica);
