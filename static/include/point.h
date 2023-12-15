#ifndef GRAYVE_POINT_H
#define GRAYVE_POINT_H

class Point {
private:
    double x;
    double z;

public:
    Point(): x(0), z(0) {};
    Point(double x, double z): x(x), z(z) {};

    [[nodiscard]] double getX() const {return x;}
    [[nodiscard]] double getZ() const {return z;}
    Point& setX(double set_x) {this->x = set_x; return *this;}
    Point& setZ(double set_z) {this->z = set_z; return *this;}
};

#endif //GRAYVE_POINT_H
