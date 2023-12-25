#include "camera.h"
#include "iostream"
#include "cmath"

void Camera::update(double interpolation) {
    if (this->follow == nullptr) return;
    this->follow->setPhi(this->getPhi());
    this->coordinates.setX(this->follow->getX() + 6 * cos(this->phi + M_PI) * sin(M_PI - this->theta));
    this->coordinates.setZ(this->follow->getZ() + 6 * sin(this->phi + M_PI) * sin(M_PI - this->theta));
    this->height = this->follow->getY() + 6 * cos(M_PI - this->theta);

    double interpolatedX = this->follow->get_interpolatedX(interpolation) + 6 * cos(this->phi + M_PI) * sin(M_PI - this->theta);
    double interpolatedZ = this->follow->get_interpolatedZ(interpolation) + 6 * sin(this->phi + M_PI) * sin(M_PI - this->theta);
    
    gluLookAt(
            interpolatedX, this->height, interpolatedZ,
            this->follow->get_interpolatedX(interpolation), this->getLookY(), this->follow->get_interpolatedZ(interpolation),
            0.0, 1.0, 0.0
    );
    glutPostRedisplay();
}
