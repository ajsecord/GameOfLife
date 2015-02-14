#ifndef GOL_UNIVERSE_H
#define GOL_UNIVERSE_H

#include <gol/gol-types.h>

/// Pointer to a universe structure.
typedef struct gol_universe *gol_universe_p;

/// Create and initialize a universe structure.
GOL_EXTERN gol_universe_p gol_create_universe();

/// Destroy a universe structure.
GOL_EXTERN void gol_destroy_universe(gol_universe_p universe);

// Return a tight bounding box containing all live cells.
GOL_EXTERN gol_int_rect gol_universe_get_bounds(gol_universe_p universe);

#endif
