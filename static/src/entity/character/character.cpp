#include "character.h"
#include "projectile.h"

void Character::shoot() {
    new Projectile(this->map, this->getPhi(), Point(this->getX(), this->getZ()), this->get_entity_type());
}