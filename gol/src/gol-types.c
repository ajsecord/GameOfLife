#include <gol/gol-types.h>

const gol_int_rect GOL_INT_RECT_EMPTY = { { 0, 0 }, { 0, 0 } };

bool gol_int_rect_is_empty(gol_int_rect rect) {
    return !(rect.size.width > 0 && rect.size.height > 0);
}
