#include <gol/gol-universe.h>

#include <gol/gol-types.h>

#include "gol-cell-internal.h"
#include "gol-cell-storage.h"
#include "gol-rand-internal.h"

#include <assert.h>
#include <stdlib.h>

static const struct gol_cell UNINITIALIZED_CELL = { GOL_CELL_UNINITIALIZED };
static const size_t TEMP_UNIVERSE_SIZE = 10;

/// Pointer to a mutating function that visits each cell in a region.
typedef bool (*gol_cell_visitor_mutating)(const gol_universe_p universe, const gol_int_coord coord, gol_cellp cell, void *user_data);

/// The universe in which the Game of Life occurs.
struct gol_universe {
    size_t generation;
    gol_int_rect bounds;
    gol_cell_storagep cells;
};

/// Mutating version of gol_universe_visit_cells().
static bool universe_visit_cells_mutating(const gol_universe_p universe, const gol_int_rect region, gol_cell_visitor_mutating visitor, void *user_data);

/// A function that flips @cell to alive with a particular probability.
/// The @user_data pointer must point to a @c gol_float that is the probability.
static bool randomly_mark_cell_as_alive(const gol_universe_p universe, const gol_int_coord coord, gol_cellp cell, void *user_data);

/// A function that applies the Game of Life rules.
static bool apply_game_of_life_rules(const gol_universe_p universe, const gol_int_coord coord, gol_cellp cell, void *user_data);


gol_universe_p gol_create_universe() {
    gol_universe_p universe = malloc(sizeof(struct gol_universe));
    universe->generation = 0;
    universe->bounds = gol_create_int_rect2(0, 0, TEMP_UNIVERSE_SIZE, TEMP_UNIVERSE_SIZE);
    const size_t num_cells = universe->bounds.size.width * universe->bounds.size.height;
    universe->cells = gol_create_cell_storage(universe->bounds);
    gol_cellp storage = gol_cell_storage_get_internal_pointer(universe->cells);
    for (size_t i = 0; i < num_cells; ++i) {
        storage[i] = gol_cell_create(GOL_CELL_UNINITIALIZED);
    }
    return universe;
}

void gol_destroy_universe(gol_universe_p universe) {
    if (universe) {
        free(universe->cells);
        free(universe);
    }
}

size_t gol_universe_get_generation(const gol_universe_p universe) {
    assert(universe);
    return universe->generation;
}

gol_int_rect gol_universe_get_bounds(gol_universe_p universe) {
    assert(universe);
    return universe->bounds;
}

const gol_cellp gol_universe_get_cell(const gol_universe_p universe, const gol_int_coord coord) {
    assert(universe);
    if (!gol_int_rect_contains_coord(universe->bounds, coord)) {
        return (const gol_cellp)&UNINITIALIZED_CELL;
    }
    const gol_cellp storage = gol_cell_storage_get_internal_pointer(universe->cells);
    // TODO: Assuming that universe->bounds == storage->bounds here.
    return &storage[gol_int_rect_coord_to_index(universe->bounds, coord)];
}

bool gol_universe_visit_cells(const gol_universe_p universe, const gol_int_rect region, gol_cell_visitor visitor, void *user_data) {
    return universe_visit_cells_mutating(universe, region, visitor, user_data);
}

void gol_universe_fill_uniformly_at_random(gol_universe_p universe, const gol_int_rect region, const gol_float prob) {
    assert(prob >= 0 && prob <= 1);
    gol_float p = prob;
    universe_visit_cells_mutating(universe, region, randomly_mark_cell_as_alive, &p);
}

void gol_universe_step(gol_universe_p universe, const size_t num_steps) {
    assert(universe);
    for (size_t i = 0; i < num_steps; ++i) {
        universe_visit_cells_mutating(universe, universe->bounds, apply_game_of_life_rules, NULL);
        ++universe->generation;
    }
}

#pragma mark - Private

bool universe_visit_cells_mutating(const gol_universe_p universe, const gol_int_rect region, gol_cell_visitor_mutating visitor, void *user_data) {
    assert(universe && visitor);
    const size_t num_cells = universe->bounds.size.width * universe->bounds.size.height;
    gol_cellp storage = gol_cell_storage_get_internal_pointer(universe->cells);
    for (size_t i = 0; i < num_cells; ++i) {
        const gol_int_coord coord = gol_int_rect_index_to_coord(universe->bounds, i);
        if (!visitor(universe, coord, storage + i, user_data)) {
            return false;
        }
    }
    return true;
}

bool randomly_mark_cell_as_alive(const gol_universe_p universe, const gol_int_coord coord, gol_cellp cell, void *user_data) {
    assert(user_data);
    const gol_float prob = *(gol_float *)user_data;
    assert(prob >= 0 && prob <= 1);

    const gol_float test = gol_rand_uniform01();

    cell->state = test < prob ? GOL_CELL_ALIVE : GOL_CELL_DEAD;
    return true;
}

bool apply_game_of_life_rules(const gol_universe_p universe, const gol_int_coord coord, gol_cellp cell, void *user_data) {
    assert(universe);

    // Don't do anything to the edges.
    if (coord.i == universe->bounds.origin.i || coord.i == universe->bounds.origin.i + universe->bounds.size.width - 1 ||
        coord.j == universe->bounds.origin.j || coord.j == universe->bounds.origin.j + universe->bounds.size.height - 1) {
        return true;
    }

    // Ignore uninitialized cells.
    if (cell->state == GOL_CELL_UNINITIALIZED) {
        return true;
    }

    // Count the number of alive cells in the 3x3 neighborhood.
    int alive_count = 0;
    gol_cellp cur_cell;
    gol_cellp storage = gol_cell_storage_get_internal_pointer(universe->cells);
    for (int j_offset = -1; j_offset <= 1; ++j_offset) {
        for (int i_offset = -1; i_offset <= 1; ++i_offset) {
            cur_cell = storage + gol_int_rect_coord_to_index(universe->bounds, gol_create_int_coord(coord.i + i_offset, coord.j + j_offset));
            alive_count += cur_cell->state == GOL_CELL_ALIVE;
        }
    }

    if (cell->state == GOL_CELL_ALIVE) {
        --alive_count;
    }

    switch (cell->state) {
        case GOL_CELL_ALIVE:
            if (!(alive_count == 2 || alive_count == 3)) {
                gol_cell_set_state(cell, GOL_CELL_DEAD, universe->generation);
            }
            break;

        case GOL_CELL_DEAD:
            if (alive_count == 3) {
                gol_cell_set_state(cell, GOL_CELL_ALIVE, universe->generation);
            }
            break;

        case GOL_CELL_UNINITIALIZED:
            break;
    }

    return true;
}

