#ifndef GRAYVE_ENTITY_H
#define GRAYVE_ENTITY_H
#include "cmath"

class Entity {
protected:
    double x, y, z;
    double phi;
    double speed;
    bool move_left, move_right, move_forward, move_backward;

    void moveLeft(double interpolation);
    void moveRight(double interpolation);
    void moveForward(double interpolation);
    void moveBackward(double interpolation);

public:
    [[nodiscard]] double getX() const {return x;}
    [[nodiscard]] double getY() const {return y;}
    [[nodiscard]] double getZ() const {return z;}
    [[nodiscard]] double getPhi() const {return phi;}
    [[nodiscard]] double getSpeed() const {return speed;}
    void update_position(double interpolation);

    Entity* setMoveLeft(bool state) {move_left = state; return this;}
    Entity* setMoveRight(bool state) {move_right = state; return this;}
    Entity* setMoveForward(bool state) {move_forward = state; return this;}
    Entity* setMoveBackward(bool state) {move_backward = state; return this;}

    void setSpeed(double set_speed) {this->speed = std::abs(set_speed);}
    void setPhi(double set_phi) {
        while (set_phi < -M_PI) set_phi += (2 * M_PI);
        while (set_phi > M_PI) set_phi -= (2 * M_PI);
        this->phi = set_phi;
    }

    [[nodiscard]] bool isMoving() const;


    Entity(): x(10), y(0), z(0), phi(0), speed(0),
              move_left(false), move_right(false), move_forward(false), move_backward(false) {}
};

#endif //GRAYVE_ENTITY_H
