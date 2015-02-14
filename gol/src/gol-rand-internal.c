#include "gol-rand-internal.h"

#include <stdlib.h>

void gol_rand_seed_generator(const unsigned seed) {
    srand(seed);
}

gol_float gol_rand_uniform01() {
    return rand() / (gol_float)RAND_MAX;
}
