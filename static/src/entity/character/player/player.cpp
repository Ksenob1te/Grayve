#include "player.h"

[[nodiscard]] EntityType Player::get_entity_type() const {
    return EntityType::PLAYER;
}

void Player::die() {};
void Player::deal_damage(Character&) {};
void Player::recieve_damage(int amount) {};

void Player::update(){
    this->update_position(*this->map);
}