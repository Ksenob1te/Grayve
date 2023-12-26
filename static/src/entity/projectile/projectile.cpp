#include "projectile.h"
#include "player.h"
#include "enemy.h"

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
        if (entity == nullptr) continue;
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
            if (this->creator_type == EntityType::ENEMY) {
                Player *plr = static_cast<Player*>(collided);
                plr->receive_damage(this->damage);
                delete this;
            }
            break;
        case EntityType::ENEMY:
            if (this->creator_type == EntityType::PLAYER) {
                Enemy *enm = static_cast<Enemy*>(collided);
                enm->receive_damage(this->damage);
                delete this;
            }
            return;
        default:
            break;
    }
}

Projectile::~Projectile() {
    this->globalMap->remove_entity(this);
}