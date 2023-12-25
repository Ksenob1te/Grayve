#include "projectile.h"
#include "player.h"

EntityType Projectile::get_entity_type() const {
    return EntityType::PROJECTILE;
}

void Projectile::update() {
    this->update_position(*this->map);
    this->update_count++;
    if(this->update_count > 1000){
        
    }
    Entity *collided;
    for (auto *entity : this->map->entity_set)
        if(this->collider.is_intersect(entity->get_collider())){
            collided = entity;
            break;
        }
    switch (collided->get_entity_type())
    {
    case EntityType::PROJECTILE:
        
        break;
    case EntityType::PLAYER:
        
        break;
    case EntityType::ENEMY:

        break;
    default:
        break;
    }
}