#include "draw_map.h"
#include "draw_block.h"
#include "draw_projectile.h"
#include "draw_player.h"
#include "draw_enemy.h"

void draw::draw_map(const field::Map &map, const Camera &camera) {
    const field::Chunk &current_chunk = map.get_starter();
    for (int x = (int) current_chunk.left_bottom.getX(); x <= current_chunk.right_top.getX(); x++) {
        for (int z = (int) current_chunk.left_bottom.getZ(); z <= current_chunk.right_top.getZ(); z++) {
            if (current_chunk.room[z][x].get_block_type() == Tile::Wall)
                if (camera.getCollider().is_intersect(current_chunk.room[z][x]))
                    continue;
            draw::draw_block(current_chunk.room[z][x]);
        }
    }
}

void draw::draw_entities(const field::Map &map, double interpolation) {
    for(const Entity* entity : map.entity_set) {
        const Entity &current_entity = *entity;
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