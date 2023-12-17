#ifndef GRAYVE_ENTITY_H
#define GRAYVE_ENTITY_H
#include "cmath"
#include "point.h"

class Entity {
protected:
    Point coordinates;
    double height;
    double phi;
    double speed;
    bool move_left, move_right, move_forward, move_backward;

    void moveLeft();
    void moveRight();
    void moveForward();
    void moveBackward();

public:
    [[nodiscard]] double getX() const {return coordinates.getX();}
    [[nodiscard]] double getY() const {return height;}
    [[nodiscard]] double getZ() const {return coordinates.getZ();}
    [[nodiscard]] double getPhi() const {return phi;}
    [[nodiscard]] double getSpeed() const {return speed;}
    [[nodiscard]] double get_interpolatedX(double interpolation) const;
    [[nodiscard]] double get_interpolatedZ(double interpolation) const;
    void setCoordinates(Point point);
    void update_position();

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


    Entity(): coordinates(Point(10, 0)), height(0), phi(0), speed(0),
              move_left(false), move_right(false), move_forward(false), move_backward(false) {};
};

#endif //GRAYVE_ENTITY_H
