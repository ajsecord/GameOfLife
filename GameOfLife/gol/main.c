#include <stdio.h>

#include <gol/gol-universe.h>

static bool print_cell(const gol_universe_p universe, const gol_int_coord coord, const gol_cell_p cell, void *user_data) {
    char c;
    switch (gol_cell_get_state(cell)) {
        case GOL_CELL_ALIVE:         c = '*'; break;
        case GOL_CELL_DEAD:          c = ' '; break;
        case GOL_CELL_UNINITIALIZED: c = '?'; break;
    }
    printf("%c", c);

    const gol_int_rect bounds = gol_universe_get_bounds(universe);
    if (coord.i == bounds.origin.i + bounds.size.width - 1) {
        printf("\n");
    }

    return true;
}

static void print_universe(const gol_universe_p universe) {
    printf("Generation %i\n", (int)gol_universe_get_generation(universe));
    gol_int_rect bounds = gol_universe_get_bounds(universe);
    gol_universe_visit_cells(universe, bounds, print_cell, NULL);
}

int main(int argc, const char *argv[]) {
    gol_universe_p universe = gol_create_universe();
    gol_int_rect bounds = gol_universe_get_bounds(universe);
    gol_universe_fill_uniformly_at_random(universe, bounds, 0.2);
    for (int i = 0; i < 10; ++i) {
        print_universe(universe);
        gol_universe_step(universe, 1);
    }
    gol_destroy_universe(universe);
    return 0;
}
