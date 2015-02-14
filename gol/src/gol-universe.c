#include "gol/gol-universe.h"

#include <stdlib.h>

/// The universe in which the Game of Life occurs.
struct gol_universe {
};

gol_universe_p gol_create_universe() {
    gol_universe_p universe = malloc(sizeof(struct gol_universe));
    return universe;
}

void gol_destroy_universe(gol_universe_p universe) {
    if (universe) {
        free(universe);
    }
}
