#ifndef GOL_CELL_INTERNAL_H
#define GOL_CELL_INTERNAL_H

#include <gol/gol-cell.h>

#include <assert.h>

struct gol_cell {
    gol_cell_state state;
    size_t last_transition_generation;
};

// Return an initialized cell in-place.
GOL_INLINE struct gol_cell gol_cell_create(const gol_cell_state state);

// Set the cell's state.
GOL_INLINE void gol_cell_set_state(gol_cellp cell, const gol_cell_state state, const size_t generation);


// Inline definitions.

GOL_INLINE struct gol_cell gol_cell_create(const gol_cell_state state) {
    struct gol_cell cell;
    cell.state = state;
    cell.last_transition_generation = 0;
    return cell;
}

GOL_INLINE void gol_cell_set_state(gol_cellp cell, const gol_cell_state state, const size_t generation) {
    assert(cell);
    if (cell->state != state) {
        cell->state = state;
        cell->last_transition_generation = generation;
    }
}

#endif
