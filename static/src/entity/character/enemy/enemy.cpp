#include "enemy.h"
#include "cmath"
#include "iostream"

[[nodiscard]] EntityType Enemy::get_entity_type() const {
    return EntityType::ENEMY;
}

std::string Enemy::get_entity_name() const {
    return "enemy";
}

void Enemy::update() {
    if (this->follow) {
        double dx = this->follow->getX() - this->getX();
        double dz = this->follow->getZ() - this->getZ();
        double at = atan(dz / dx);
        double phi;
        if (dx > 0)
            phi = at;
        else if (dz > 0)
            phi = at + M_PI;
        else
            phi = at - M_PI;
        this->setPhi(phi);
        this->setMoveForward(true);

        if (sqrt(dx * dx + dz * dz) <= 5)
            if (this->shoot_cooldown == 0) {
//                std::cout << this->health_points << std::endl;
                this->shoot();
                this->shoot_cooldown = SHOOT_COOLDOWN;
            }
        if (sqrt(dx * dx + dz * dz) <= 4)
            this->setMoveForward(false);

    }
    Character::update();
}
