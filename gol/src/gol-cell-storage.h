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

/// Return a pointer to the internal cell storage.
GOL_EXTERN gol_cellp gol_cell_storage_get_internal_pointer(gol_cell_storagep storage);

#endif
