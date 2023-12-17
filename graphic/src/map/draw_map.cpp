#include "draw_map.h"
#include "draw_block.h"

void draw::draw_map(const field::Map &map) {
    const field::Chunk &current_chunk = map.get_starter();
    for (int x = (int) current_chunk.left_bottom.getX(); x <= current_chunk.right_top.getX(); x++) {
        for (int z = (int) current_chunk.left_bottom.getZ(); z <= current_chunk.right_top.getZ(); z++) {
            draw::draw_block(map.get_starter().room[z][x]);
        }
    }
}