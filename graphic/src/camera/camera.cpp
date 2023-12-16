#include "camera.h"
#include "iostream"
#include "cmath"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void Camera::update() {
    if (this->follow == nullptr) return;
    this->follow->setPhi(this->phi);
    this->follow->update_position(1);
    this->x = this->follow->getX() - 6 * acos(this->phi);
    this->z = this->follow->getZ() - 6 * asin(this->phi);

    glutPostRedisplay();
}
