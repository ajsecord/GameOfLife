#include <gol/gol-universe.h>

#include "gol-cell-internal.h"
#include "gol-rand-internal.h"

#include <assert.h>
#include <stdlib.h>

static const struct gol_cell UNINITIALIZED_CELL = { GOL_CELL_UNINITIALIZED };

/// Pointer to a mutating function that visits each cell in a region.
typedef bool (*gol_cell_visitor_mutating)(const gol_universe_p universe, const gol_int_coord coord, gol_cell_p cell, void *user_data);

/// The universe in which the Game of Life occurs.
struct gol_universe {
};

/// Mutating version of gol_universe_visit_cells().
static bool universe_visit_cells_mutating(const gol_universe_p universe, const gol_int_rect region, gol_cell_visitor_mutating visitor, void *user_data);

/// A function that flips @cell to alive with a particular probability.
/// The @user_data pointer must point to a @c gol_float that is the probability.
static bool randomly_mark_cell_as_alive(const gol_universe_p universe, const gol_int_coord coord, gol_cell_p cell, void *user_data);

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

const gol_cell_p gol_universe_get_cell(const gol_universe_p universe, const gol_int_coord coord) {
    // TODO: Can we get around this cast?
    return (const gol_cell_p)&UNINITIALIZED_CELL;
}

void gol_universe_fill_uniformly_at_random(gol_universe_p universe, const gol_int_rect region, const gol_float prob) {
    assert(prob >= 0 && prob <= 1);
    gol_float p = prob;
    universe_visit_cells_mutating(universe, region, randomly_mark_cell_as_alive, &p);
}

bool gol_universe_visit_cells(const gol_universe_p universe, const gol_int_rect region, gol_cell_visitor visitor, void *user_data) {
    return false;
}

#pragma mark - Private

bool universe_visit_cells_mutating(const gol_universe_p universe, const gol_int_rect region, gol_cell_visitor_mutating visitor, void *user_data) {
    return false;
}

bool randomly_mark_cell_as_alive(const gol_universe_p universe, const gol_int_coord coord, gol_cell_p cell, void *user_data) {
    assert(user_data);
    const gol_float prob = *(gol_float *)user_data;
    assert(prob >= 0 && prob <= 1);

    const gol_float test = gol_rand_uniform01();

    cell->state = test < prob ? GOL_CELL_ALIVE : GOL_CELL_DEAD;
    return true;
}



