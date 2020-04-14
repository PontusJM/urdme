/* urdmerng.h - URDME random number generators */

/* P. Melin 2020-04-09 */

typedef unsigned int rand_state_t;

/* rng codes */
#define RAND_R 1
#define DRAND48 2

/* select sampling function at compile time 
   default to drand48() */
#if URDMERNG == RAND_R
#define sample_rng(rng) ((double) rand_r((rng)) / (double) RAND_MAX)
#else
#define sample_rng(rng) (double) drand48()
#endif

/* Initializes a random number generator with seed */
rand_state_t *init_rng(rand_state_t seed);

/* Destroys a random number generator */
void destroy_rng(rand_state_t *rng);
