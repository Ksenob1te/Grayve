#include "camera.h"
#include "iostream"
#include "cmath"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void Camera::update() {
    struct Vector {
        double x, y, z;
        static void rotate_system_positive(Vector &v, double phi) {
            double x = v.x * cos(phi) + v.z * sin(phi);
            double z = - v.x * sin(phi) + v.z * cos(phi);
            v.x = x;
            v.z = z;
        }
        static void rotate_system_negative(Vector &v, double phi) {
            double x = v.x * cos(phi) - v.z * sin(phi);
            double z = v.x * sin(phi) + v.z * cos(phi);
            v.x = x;
            v.z = z;
        }
    };

    if (this->follow == nullptr) return;
    this->follow->setPhi(this->phi);
    this->follow->update_position(1);
    this->setSpeed(this->follow->getSpeed());
    Vector look_at_follow = {
                (this->follow->getX() - this->x),
                (this->follow->getY() - this->y),
                (this->follow->getZ() - this->z)
            };
    if (this->phi > 0)
        Vector::rotate_system_positive(look_at_follow, this->phi);
    else
        Vector::rotate_system_negative(look_at_follow, abs(this->phi));
//    std::cout << look_at_follow.x << " " << look_at_follow.z << std::endl;
    if (look_at_follow.x > 8)
        this->setMoveForward(true);
    else if (look_at_follow.x < 5)
        this->setMoveBackward(true);
    else {
        this->setMoveForward(false);
        this->setMoveBackward(false);
    }

    if (look_at_follow.z > 2)
        this->setMoveRight(true);
    else if (look_at_follow.z < -2)
        this->setMoveLeft(true);
    else {
        this->setMoveRight(false);
        this->setMoveLeft(false);
    }
    this->update_position(1);
    glutPostRedisplay();
}
