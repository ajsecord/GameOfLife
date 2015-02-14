#ifndef GOL_CELL_INTERNAL_H
#define GOL_CELL_INTERNAL_H

#include <gol/gol-cell.h>

struct gol_cell {
    gol_cell_state state;
};

// Return an initialized cell in-place.
struct gol_cell gol_cell_create(const gol_cell_state state);

#endif
