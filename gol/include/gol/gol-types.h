#ifndef GOL_TYPES_H
#define GOL_TYPES_H

#include <stdbool.h>

#include <gol/gol-defines.h>

/// The floating-point type.
typedef float gol_float;

/// A 2D point with integer coordinates.
typedef struct {
    int i;
    int j;
} gol_int_coord;

/// A 2D size with integer values.
typedef struct {
    int width;
    int height;
} gol_int_size;

/// A 2D rectangle with integer values.
typedef struct {
    gol_int_coord origin;
    gol_int_size size;
} gol_int_rect;

/// Returns true if a rectangle is empty.
bool gol_int_rect_is_empty(gol_int_rect rect);

/// The empty gol_int_rect;
GOL_EXTERN const gol_int_rect GOL_INT_RECT_EMPTY;

#endif
