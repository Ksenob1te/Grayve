#ifndef GRAYVE_CAMERA_H
#define GRAYVE_CAMERA_H

#include "cmath"
#include "entity.h"
#include "GL/glut.h"

class Camera: public Entity {
private:
    double theta;
    double phi;

public:
    Entity *follow;
    Camera(): theta(2.5 * M_PI / 4), phi(0), follow(nullptr) {y = 4; x = 0; z = 0;}
    [[nodiscard]] double getLookX() const {return cos(phi) * sin(theta);}
    [[nodiscard]] double getLookY() const {return cos(theta);}
    [[nodiscard]] double getLookZ() const {return sin(phi) * sin(theta);}

    void changeTheta(double amount) {if (theta + amount >= 0 && theta + amount <= M_PI) theta += amount;}
    void update();
};

#endif //GRAYVE_CAMERA_H
