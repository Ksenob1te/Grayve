#include "projectile.h"
#include "player.h"

EntityType Projectile::get_entity_type() const {
    return EntityType::PROJECTILE;
}

void Projectile::update() {
    this->update_position();
    this->life_time++;
    if (this->life_time > 100 || this->lock_dx || this->lock_dz) {
        delete this;
        return;
    }
    Entity *collided = nullptr;
    for (auto *entity: this->globalMap->entity_set) {
        if (this == entity) continue;
        if (this->collider.is_intersect(entity->get_collider())) {
            collided = entity;
            break;
        }
    }
    if (collided == nullptr) return;

    switch (collided->get_entity_type()) {
        case EntityType::PROJECTILE:
            delete collided;
            delete this;
            return;
        case EntityType::PLAYER:

            break;
        case EntityType::ENEMY:
            printf("COLLIDED\n");
            delete this;
            return;
        default:
            break;
    }
}