#include "gol-cell-storage.h"

#include "gol-cell-internal.h"

#include <stdlib.h>
#include <string.h>

struct gol_cell_storage {
    gol_int_rect bounds;
    gol_cellp cells;
};

gol_cell_storagep gol_create_cell_storage(const gol_int_rect bounds) {
    gol_cell_storagep storage = malloc(sizeof(struct gol_cell_storage));
    if (!storage) {
        return NULL;
    }
    
    storage->bounds = bounds;

    const size_t num_cells = gol_cell_storage_get_num_cells(storage);
    storage->cells = malloc(num_cells * sizeof(struct gol_cell));
    if (!storage->cells) {
        free(storage);
        return NULL;
    }

    return storage;
}

void gol_destory_cell_storage(gol_cell_storagep storage) {
    if (storage) {
        assert(storage->cells);
        free(storage->cells);
        free(storage);
    }
}

gol_int_rect gol_cell_storage_get_bounds(const gol_cell_storagep storage) {
    assert(storage);
    return storage->bounds;
}

size_t gol_cell_storage_get_num_cells(const gol_cell_storagep storage) {
    return storage->bounds.size.width * storage->bounds.size.height;
}

gol_cellp gol_cell_storage_get_internal_pointer(gol_cell_storagep storage) {
    assert(storage);
    return storage->cells;
}

void gol_cell_storage_copy_contents(gol_cell_storagep storage, gol_cell_storagep other) {
    assert(gol_cell_storage_get_num_cells(storage) == gol_cell_storage_get_num_cells(other));
    memcpy(other->cells, storage->cells, gol_cell_storage_get_num_cells(storage) * sizeof(struct gol_cell));
}

