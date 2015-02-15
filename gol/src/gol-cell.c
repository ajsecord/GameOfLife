#include <gol/gol-cell.h>

#include "gol-cell-internal.h"

#include <assert.h>

gol_cell_state gol_cell_get_state(const gol_cellp cell) {
    assert(cell);
    return cell->state;
}

size_t gol_cell_get_last_transition_generation(const gol_cellp cell) {
    assert(cell);
    return cell->last_transition_generation;
}
