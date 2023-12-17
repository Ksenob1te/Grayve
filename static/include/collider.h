#ifndef GRAYVE_COLLIDER_H
#define GRAYVE_COLLIDER_H
#include "block.h"

class Cylinder {
protected:
    Point *center;
    double radius;
public:
    Cylinder(): center(nullptr), radius(0) {};
    Cylinder(Point *point): center(point), radius(0) {};
    Cylinder(Point *point, double radius): center(point), radius(radius) {};
    ~Cylinder() = default;
};

class ColliderBox: public Cylinder {
private:

public:
    bool is_intersect(ColliderBox &other);
    bool is_intersect(Block &other);

};

#endif //GRAYVE_COLLIDER_H
