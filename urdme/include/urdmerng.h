/* urdmerng.h - URDME random number generators */

/* P. Melin 2020-04-09 */

/* rng codes */
#define RAND_R 1
#define DRAND48 2

typedef int RngType;

typedef struct{
  RngType type;
  unsigned int state;
}rng_t;

/* Initializes a random number generator 
   params: type the rng code
           seed the seed to the rng */
rng_t *init_rng(RngType type, unsigned int seed);

/* Destroys a random number generator */
void destroy_rng(rng_t *rng);

/* Samples from the random number generator rng
   returns: a value x s.t. 0 < x <= 1 */
double rand_sample(rng_t *rng);
