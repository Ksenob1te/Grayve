#include "player.h"

[[nodiscard]] EntityType Player::get_entity_type() const {
    return EntityType::PLAYER;
}

void Player::die() {};
void Player::deal_damage(Character&) {};
void Player::receive_damage(int amount) {};

void Player::update(){

    if (this->sprint_length) this->sprint_length--;
    if (this->sprint_cooldown) this->sprint_cooldown--;

    if (this->shoot_action && this->shoot_cooldown == 0) {
        this->shoot();
        this->shoot_cooldown = SHOOT_COOLDOWN;
    }
    if (this->sprint_action) {
        this->sprint_action = false;
        if (this->sprint_cooldown == 0) {
            this->setSpeed(DEFAULT_SPEED * 2);
            this->sprint_cooldown = SPRINT_COOLDOWN;
            this->sprint_length = SPRINT_LENGTH;
        }
    }
    if (this->sprint_length == 0)
        this->setSpeed(DEFAULT_SPEED);

    Character::update();
}