#include "creeper.h"
#include "texture_manager.h"

std::string Creeper::get_entity_name() const {
    return "creeper";
}


void Creeper::die() {
    int amount = 12;
    for (int i = 0; i < amount; i++) {
        this->setPhi(this->getPhi() + (M_PI * 2 / amount));
        this->shoot();
    }
    delete this;
}


void Creeper::update() {
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

        if (sqrt(dx * dx + dz * dz) <= 3) {
            if (this->explosion_timer == 0) {
                this->die();
                return;
            }
            explosion_timer--;
        } else
            explosion_timer = EXPLOSION_TIMER;
        if (sqrt(dx * dx + dz * dz) <= 1)
            this->setMoveForward(false);
    }
    Character::update();
}

static Creeper creeper(nullptr);