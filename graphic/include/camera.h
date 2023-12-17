#ifndef GRAYVE_CAMERA_H
#define GRAYVE_CAMERA_H

#include "cmath"
#include "entity.h"
#include "GL/glut.h"

class Camera {
private:
    double theta, phi;
    Point coordinates;
    double height;

public:
    Entity *follow;
    Camera(): theta(2.5 * M_PI / 4), phi(0), follow(nullptr) {coordinates = Point(0, 0); height = 0;}

    [[nodiscard]] double getLookX() const {return follow->getX();}
    [[nodiscard]] double getLookY() const {return follow->getY() + 2;}
    [[nodiscard]] double getLookZ() const {return follow->getZ();}
    [[nodiscard]] double getPhi() const {return this->phi;}
    [[nodiscard]] double getTheta() const {return this->theta;}
    void setPhi(double set_phi) {
        while (set_phi < -M_PI) set_phi += (2 * M_PI);
        while (set_phi > M_PI) set_phi -= (2 * M_PI);
        this->phi = set_phi;
    }

    void changeTheta(double amount) {if (theta + amount >= 6 * M_PI / 10 && theta + amount <= M_PI) theta += amount;}
    void update(double interpolation);
};

#endif //GRAYVE_CAMERA_H
