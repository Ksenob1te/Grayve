#ifndef GRAYVE_DRAW_MAP_H
#define GRAYVE_DRAW_MAP_H
#include "map.h"

namespace draw {
    void draw_map(const field::Map &map);
    void draw_entities(const field::Map &map, double interpolation);
}
#endif //GRAYVE_DRAW_MAP_H
