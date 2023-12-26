#ifndef GRAYVE_DRAW_MAP_H
#define GRAYVE_DRAW_MAP_H
#include "map.h"
#include "camera.h"

namespace draw {
    void draw_map(const field::Map &map, const Camera &camera);
    void draw_entities(const field::Map &map, double interpolation);
}
#endif //GRAYVE_DRAW_MAP_H
