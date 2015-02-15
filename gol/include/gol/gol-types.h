#ifndef GOL_TYPES_H
#define GOL_TYPES_H

#include <gol/gol-defines.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

/// The floating-point type.
typedef float gol_float;

/// A 2D point with integer coordinates.
typedef struct {
    int i;
    int j;
} gol_int_coord;

/// Returns a gol_int_coord initialized with particular values.
GOL_INLINE gol_int_coord gol_create_int_coord(const int i, const int j);

/// Returns true if @coord equals @other.
GOL_INLINE bool gol_int_coord_is_equal(const gol_int_coord coord, const gol_int_coord other);

/// A 2D size with integer values.
typedef struct {
    int width;
    int height;
} gol_int_size;

/// Returns a gol_int_size initialized with particular values.
GOL_INLINE gol_int_size gol_create_int_size(const int width, const int height);

/// Returns true if @size equals @other.
GOL_INLINE bool gol_int_size_is_equal(const gol_int_size size, const gol_int_size other);

/// A 2D rectangle with integer values.
typedef struct {
    gol_int_coord origin;
    gol_int_size size;
} gol_int_rect;

/// The empty gol_int_rect.
GOL_EXTERN const gol_int_rect GOL_INT_RECT_EMPTY;

/// Create a gol_int_rect with particular values.
GOL_INLINE gol_int_rect gol_create_int_rect(const gol_int_coord origin, const gol_int_size size);

/// Create a gol_int_rect with particular values.
GOL_INLINE gol_int_rect gol_create_int_rect2(const int i, const int j, const int width, const int height);

/// Returns true if a rectangle is empty.
GOL_INLINE bool gol_int_rect_is_empty(gol_int_rect rect);

/// Returns true if @rect equals @other.
GOL_INLINE bool gol_int_rect_is_equal(const gol_int_rect rect, const gol_int_rect other);

/// Returns true if @coord is contained in @rect.
GOL_INLINE bool gol_int_rect_contains_coord(const gol_int_rect rect, const gol_int_coord coord);

/// Convert a coordinate in @rect to an array index.
GOL_INLINE size_t gol_int_rect_coord_to_index(const gol_int_rect rect, const gol_int_coord coord);

/// Convert an array index to a coordinate in @rect.
GOL_INLINE gol_int_coord gol_int_rect_index_to_coord(const gol_int_rect rect, const size_t index);



//
// Definitions of inline functions.
//

GOL_INLINE gol_int_coord gol_create_int_coord(int i, int j) {
    gol_int_coord coord = { i, j };
    return coord;
}

GOL_INLINE bool gol_int_coord_is_equal(const gol_int_coord coord, const gol_int_coord other) {
    return coord.i == other.i && coord.j == other.j;
}


GOL_INLINE gol_int_size gol_create_int_size(const int width, const int height) {
    gol_int_size size = { width, height };
    return size;
}

GOL_INLINE bool gol_int_size_is_equal(const gol_int_size size, const gol_int_size other) {
    return size.width == other.width && size.height == other.height;
}


GOL_INLINE gol_int_rect gol_create_int_rect(const gol_int_coord origin, const gol_int_size size) {
    gol_int_rect rect = { origin, size };
    return rect;
}

GOL_INLINE gol_int_rect gol_create_int_rect2(const int i, const int j, const int width, const int height) {
    return gol_create_int_rect(gol_create_int_coord(i, j), gol_create_int_size(width, height));
}

GOL_INLINE bool gol_int_rect_is_empty(gol_int_rect rect) {
    return !(rect.size.width > 0 && rect.size.height > 0);
}

GOL_INLINE bool gol_int_rect_is_equal(const gol_int_rect rect, const gol_int_rect other) {
    return gol_int_coord_is_equal(rect.origin, other.origin) && gol_int_size_is_equal(rect.size, other.size);
}

GOL_INLINE bool gol_int_rect_contains_coord(const gol_int_rect rect, const gol_int_coord coord) {
    return coord.i >= rect.origin.i &&
           coord.j >= rect.origin.j &&
           coord.i < rect.origin.i + rect.size.width &&
           coord.j < rect.origin.j + rect.size.height;
}

GOL_INLINE size_t gol_int_rect_coord_to_index(const gol_int_rect rect, const gol_int_coord coord) {
    assert(gol_int_rect_contains_coord(rect, coord));
    const int x = coord.i - rect.origin.i;
    const int y = coord.j - rect.origin.j;
    return y * rect.size.width + x;
}

GOL_INLINE gol_int_coord gol_int_rect_index_to_coord(const gol_int_rect rect, const size_t index) {
    assert(index < rect.size.width * rect.size.height);
    return gol_create_int_coord(rect.origin.i + index % rect.size.width,
                                rect.origin.j + (int)(index / rect.size.height));
}


#endif
