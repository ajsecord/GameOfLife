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

gol_int_rect gol_universe_get_bounds(gol_universe_p universe) {
    return GOL_INT_RECT_EMPTY;
}

