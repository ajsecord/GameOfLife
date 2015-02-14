#ifndef GOL_UNIVERSE_H
#define GOL_UNIVERSE_H

#include <stdbool.h>

#include <gol/gol-types.h>
#include <gol/gol-cell.h>

/// Pointer to a universe structure.
typedef struct gol_universe *gol_universe_p;

/// Pointer to a function that visits each cell in a region.
/// @param universe The universe in which cells are being visited.
/// @param coord The coordinate of the current cell.
/// @param cell The current cell.
/// @param user_data The user_data parameter passed to gol_universe_visit_cells().
/// @return True if the iteration should continue, otherwise false.
typedef bool (*gol_cell_visitor)(const gol_universe_p universe, const gol_int_coord coord, const gol_cell_p cell, void *user_data);

/// Create and initialize a universe structure.
GOL_EXTERN gol_universe_p gol_create_universe();

/// Destroy a universe structure.
GOL_EXTERN void gol_destroy_universe(gol_universe_p universe);

/// Return a tight bounding box containing all live cells.
GOL_EXTERN gol_int_rect gol_universe_get_bounds(const gol_universe_p universe);

/// Return the cell at a particular location.
GOL_EXTERN const gol_cell_p gol_universe_get_cell(const gol_universe_p universe, const gol_int_coord coord);

/// Fill @c region with randomly alive/dead cells with probability @prob of being alive.
GOL_EXTERN void gol_universe_fill_uniformly_at_random(gol_universe_p universe, const gol_int_rect region, const gol_float prob);

/// Visit each cell in @c region and call visitor() on the cell.
/// @param universe The universe to visit cells in.
/// @param region The region to iterate over.
/// @param visitor The visitor function to call for each cell.
/// @param user_data A user-defined pointer that will be passed into visitor() and otherwise left untouched.
/// @return True if visitor() never aborted the iteration, otherwise false.
GOL_EXTERN bool gol_universe_visit_cells(const gol_universe_p universe, const gol_int_rect region, gol_cell_visitor visitor, void *user_data);

#endif
