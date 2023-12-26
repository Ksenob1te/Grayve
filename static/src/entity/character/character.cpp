#include "character.h"
#include "projectile.h"
#include "iostream"

void Character::shoot() {
    new Projectile(this->globalMap, this->getPhi(), Point(this->getX(), this->getZ()), this->get_entity_type());
}

void Character::update() {
    Entity::update();
}