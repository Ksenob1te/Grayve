#ifndef GRAYVE_COLLIDER_H
#define GRAYVE_COLLIDER_H
#include "block.h"

class Cylinder {
protected:
    Point *center;
    double radius;
public:
    Cylinder(): center(nullptr), radius(0) {};
    explicit Cylinder(Point *point): center(point), radius(0) {};
    Cylinder(Point *point, double radius): center(point), radius(radius) {};
    ~Cylinder() = default;
};

class ColliderBox: public Cylinder {
public:
    bool is_intersect(ColliderBox &other);
    bool is_intersect(const Block &other);
    ColliderBox(): Cylinder() {};
    explicit ColliderBox(Point *point): Cylinder(point) {};
    ColliderBox(Point *point, double radius): Cylinder(point, radius) {};
    void set_center(Point *point) {this->center = point;}
    void set_radius(double radius) {this->radius = radius;}
};

#endif //GRAYVE_COLLIDER_H
