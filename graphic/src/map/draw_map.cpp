#include "draw_map.h"
#include "draw_block.h"
#include "draw_projectile.h"
#include "draw_player.h"
#include "draw_enemy.h"


void draw::draw_map(const field::Map &map, const Camera &camera, int chunk_x, int chunk_y) {
    const field::Chunk &current_chunk = map.get_chunk(chunk_x, chunk_y);
    for (int x = (int) current_chunk.left_bottom.getX(); x <= current_chunk.right_top.getX(); x++) {
        for (int z = (int) current_chunk.left_bottom.getZ(); z <= current_chunk.right_top.getZ(); z++) {
            if (current_chunk.room[z][x].get_block_type() == Tile::Wall)
                if (camera.getCollider().is_intersect(current_chunk.room[z][x]))
                    continue;
            draw::draw_block(current_chunk.room[z][x]);
        }
    }

    auto draw_block_camera = [&](int z, int x) {
        if (current_chunk.room[z][x].get_block_type() == Tile::Wall)
            if (camera.getCollider().is_intersect(current_chunk.room[z][x]))
                return;
        draw::draw_block(current_chunk.room[z][x]);
    };

    if (current_chunk.room[field::CHUNK_SIZE / 2][0].get_block_type() == Tile::Floor)
        for (int x = 0; x < (int) current_chunk.left_bottom.getX(); x++) {
            draw_block_camera(field::CHUNK_SIZE / 2 - 1, x);
            draw_block_camera(field::CHUNK_SIZE / 2, x);
            draw_block_camera(field::CHUNK_SIZE / 2 + 1, x);
        }

    if (current_chunk.room[field::CHUNK_SIZE / 2][field::CHUNK_SIZE - 1].get_block_type() == Tile::Floor)
        for (int x = (int) current_chunk.right_top.getX() + 1; x < field::CHUNK_SIZE; x++) {
            draw_block_camera(field::CHUNK_SIZE / 2 - 1, x);
            draw_block_camera(field::CHUNK_SIZE / 2, x);
            draw_block_camera(field::CHUNK_SIZE / 2 + 1, x);
        }

    if (current_chunk.room[0][field::CHUNK_SIZE / 2].get_block_type() == Tile::Floor)
        for (int z = 0; z < (int) current_chunk.left_bottom.getZ(); z++) {
            draw_block_camera(z, field::CHUNK_SIZE / 2 - 1);
            draw_block_camera(z, field::CHUNK_SIZE / 2);
            draw_block_camera(z, field::CHUNK_SIZE / 2 + 1);
        }

    if (current_chunk.room[field::CHUNK_SIZE - 1][field::CHUNK_SIZE / 2].get_block_type() == Tile::Floor)
        for (int z = (int) current_chunk.right_top.getZ() + 1; z < field::CHUNK_SIZE; z++) {
            draw_block_camera(z, field::CHUNK_SIZE / 2 - 1);
            draw_block_camera(z, field::CHUNK_SIZE / 2);
            draw_block_camera(z, field::CHUNK_SIZE / 2 + 1);
        }
}

void draw::draw_entities(const field::Map &map, double interpolation, int chunk_x, int chunk_y) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(const Entity* entity : map.entity_set) {
        const Entity &current_entity = *entity;
        if (entity->get_chunk_x() == chunk_x && entity->get_chunk_y() == chunk_y)
        switch (entity->get_entity_type()) {
            case EntityType::PROJECTILE:
                draw::draw_projectile(current_entity, interpolation);
                break;
            case EntityType::PLAYER:
                draw::draw_player(current_entity, interpolation);
                break;
            case EntityType::ENEMY:
                draw::draw_enemy(current_entity, interpolation);
                break;
            default:
                break;
        }
    }

}