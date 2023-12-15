#ifndef GRAYVE_DRAW_BLOCK_H
#define GRAYVE_DRAW_BLOCK_H
#include "block.h"

namespace draw {
    void draw_floor(const Block &floor_block);
    void draw_void(const Block &void_block);
    void draw_small_wall(const Block &s_wall_block);
    void draw_wall(const Block &wall_block);

    void draw_block(const Block &block);
};

#endif
