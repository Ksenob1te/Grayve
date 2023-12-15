#include "entity.h"

void Entity::moveForward(double interpolation) {
    double look_x = cos(this->phi);
    double look_z = sin(this->phi);
    this->x += (look_x * this->speed * interpolation);
    this->z += (look_z * this->speed * interpolation);
}

void Entity::moveBackward(double interpolation) {
    double look_x = cos(this->phi);
    double look_z = sin(this->phi);
    this->x -= (look_x * this->speed * interpolation);
    this->z -= (look_z * this->speed * interpolation);
}

void Entity::moveLeft(double interpolation) {
    double look_x = cos(this->phi + M_PI_2);
    double look_z = sin(this->phi + M_PI_2);
    this->x -= (look_x * this->speed * interpolation);
    this->z -= (look_z * this->speed * interpolation);
}

void Entity::moveRight(double interpolation) {
    double look_x = cos(this->phi - M_PI_2);
    double look_z = sin(this->phi - M_PI_2);
    this->x -= (look_x * this->speed * interpolation);
    this->z -= (look_z * this->speed * interpolation);
}

void Entity::update_position(double interpolation) {
    if (this->move_forward) this->moveForward(interpolation);
    if (this->move_backward) this->moveBackward(interpolation);
    if (this->move_left) this->moveLeft(interpolation);
    if (this->move_right) this->moveRight(interpolation);
}

bool Entity::isMoving() const {
    return bool(this->move_right || this->move_left || this->move_backward || this->move_forward);
}
