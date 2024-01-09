#include "character.h"
#include "projectile.h"
#include "iostream"

void Character::shoot() {
    new Projectile(this->globalMap, this->getPhi(), Point(this->getX(), this->getZ()),
                   this->get_entity_type(), this->chunk_x, this->chunk_y);
}

void Character::update() {
    if (this->shoot_cooldown) this->shoot_cooldown--;
    Entity::update();
}

void Character::receive_damage(int amount) {
    health_points -= amount;
    if (this->health_points <= 0) this->die();
}

void Character::die() {
    delete this;
}