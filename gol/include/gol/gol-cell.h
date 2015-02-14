#ifndef GOL_CELL_H
#define GOL_CELL_H

#include <gol/gol-types.h>

// The states that a cell can be in.
typedef enum {
    GOL_CELL_UNINITIALIZED,     ///< The cell has not been initialized yet.
    GOL_CELL_DEAD,              ///< The cell is dead.
    GOL_CELL_ALIVE              ///< The cell is alive.
} gol_cell_state;

typedef struct gol_cell *gol_cell_p;

GOL_EXTERN gol_cell_state gol_cell_get_state(const gol_cell_p cell);

#endif
