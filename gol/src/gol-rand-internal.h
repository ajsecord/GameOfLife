#ifndef GOL_RAND_INTERNAL_H
#define GOL_RAND_INTERNAL_H

#include <gol/gol-types.h>

/// Seed the random number generator.
void gol_rand_seed_generator(const unsigned seed);

/// Return a floating-point number uniformly at random in [0,1].
gol_float gol_rand_uniform01();

#endif