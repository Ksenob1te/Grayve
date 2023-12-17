#include "entity.h"


void Entity::moveForward() {
    double look_x = cos(this->phi);
    double look_z = sin(this->phi);
    this->coordinates.setX(this->coordinates.getX() + (look_x * this->speed));
    this->coordinates.setZ(this->coordinates.getZ() + (look_z * this->speed));
}

void Entity::moveBackward() {
    double look_x = cos(this->phi);
    double look_z = sin(this->phi);
    this->coordinates.setX(this->coordinates.getX() - (look_x * this->speed));
    this->coordinates.setZ(this->coordinates.getZ() - (look_z * this->speed));
}

void Entity::moveLeft() {
    double look_x = cos(this->phi + M_PI_2);
    double look_z = sin(this->phi + M_PI_2);
    this->coordinates.setX(this->coordinates.getX() - (look_x * this->speed));
    this->coordinates.setZ(this->coordinates.getZ() - (look_z * this->speed));
}

void Entity::moveRight() {
    double look_x = cos(this->phi - M_PI_2);
    double look_z = sin(this->phi - M_PI_2);
    this->coordinates.setX(this->coordinates.getX() - (look_x * this->speed));
    this->coordinates.setZ(this->coordinates.getZ() - (look_z * this->speed));
}

void Entity::update_position() {
    if (this->move_forward) this->moveForward();
    if (this->move_backward) this->moveBackward();
    if (this->move_left) this->moveLeft();
    if (this->move_right) this->moveRight();
}

bool Entity::isMoving() const {
    return bool(this->move_right || this->move_left || this->move_backward || this->move_forward);
}

void Entity::setCoordinates(Point point) {
    this->coordinates = point;
}

double Entity::get_interpolatedX(double interpolation) const {
    if (!this->isMoving()) return this->coordinates.getX();
    double dx = 0;
    if (move_forward)
        dx += cos(this->phi) * this->speed * interpolation;
    if (move_backward)
        dx -= cos(this->phi) * this->speed * interpolation;
    if (move_right)
        dx -= cos(this->phi - M_PI_2) * this->speed * interpolation;
    if (move_left)
        dx -= cos(this->phi + M_PI_2) * this->speed * interpolation;
    return this->coordinates.getX() + dx;
}

double Entity::get_interpolatedZ(double interpolation) const {
    if (!this->isMoving()) return this->coordinates.getZ();
    double dz = 0;
    if (move_forward)
        dz += sin(this->phi) * this->speed * interpolation;
    if (move_backward)
        dz -= sin(this->phi) * this->speed * interpolation;
    if (move_right)
        dz -= sin(this->phi - M_PI_2) * this->speed * interpolation;
    if (move_left)
        dz -= sin(this->phi + M_PI_2) * this->speed * interpolation;
    return this->coordinates.getZ() + dz;
}