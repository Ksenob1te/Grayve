#include "player.h"


[[nodiscard]] EntityType Player::get_entity_type() const {
    return EntityType::PLAYER;
}

std::string Player::get_entity_name() const {
    return "player";
}

void Player::die() {};
void Player::receive_damage(int amount) {};

void Player::update(){

    if (this->getZ() < 0) {this->chunk_x--; this->setCoordinates(Point(this->getX(), field::CHUNK_SIZE));}
    if (this->getZ() > field::CHUNK_SIZE) {this->chunk_x++; this->setCoordinates(Point(this->getX(), 0));}
    if (this->getX() < 0) {this->chunk_y--; this->setCoordinates(Point(field::CHUNK_SIZE, this->getZ()));}
    if (this->getX() > field::CHUNK_SIZE) {this->chunk_y++; this->setCoordinates(Point(0, this->getZ()));}

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