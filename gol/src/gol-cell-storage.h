#ifndef GOL_CELL_STORAGE_H
#define GOL_CELL_STORAGE_H

#include <gol/gol-cell.h>
#include <gol/gol-types.h>

/// Pointer to cell storage.
typedef struct gol_cell_storage *gol_cell_storagep;

/// Create cell storage for @bounds.
GOL_EXTERN gol_cell_storagep gol_create_cell_storage(const gol_int_rect bounds);

/// Destory cell storage.
GOL_EXTERN void gol_destory_cell_storage(gol_cell_storagep storage);

/// Return the bounds of the storage.
GOL_EXTERN gol_int_rect gol_cell_storage_get_bounds(const gol_cell_storagep storage);

/// Return the number of cells in the storage.
GOL_EXTERN size_t gol_cell_storage_get_num_cells(const gol_cell_storagep storage);

/// Return a pointer to the internal cell storage.
GOL_EXTERN gol_cellp gol_cell_storage_get_internal_pointer(gol_cell_storagep storage);

/// Copy the contents of @c other's cell storage to @c storage. The sizes of the two bounds must be equal.
GOL_EXTERN void gol_cell_storage_copy_contents(gol_cell_storagep storage, gol_cell_storagep other);

#endif
