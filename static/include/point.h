#ifndef GRAYVE_POINT_H
#define GRAYVE_POINT_H

/**
 * @class Point
 * @brief Represents a point in a 2D space with X and Z coordinates.
 */
class Point {
private:
    double x; /**< X-coordinate of the point. */
    double z; /**< Z-coordinate of the point. */

public:
    /**
     * @brief Default constructor for Point class.
     * @details Initializes the point with coordinates (0, 0).
     */
    Point(): x(0), z(0) {};

    /**
     * @brief Parameterized constructor for Point class.
     * @param x The X-coordinate of the point.
     * @param z The Z-coordinate of the point.
     */
    Point(double x, double z): x(x), z(z) {};

    /**
     * @brief Gets the X-coordinate of the point.
     * @return The X-coordinate.
     */
    [[nodiscard]] double getX() const { return x; }

    /**
     * @brief Gets the Z-coordinate of the point.
     * @return The Z-coordinate.
     */
    [[nodiscard]] double getZ() const { return z; }

    /**
     * @brief Sets the X-coordinate of the point.
     * @param set_x The new X-coordinate to be set.
     * @return Reference to the updated Point object.
     */
    Point& setX(double set_x) { this->x = set_x; return *this; }

    /**
     * @brief Sets the Z-coordinate of the point.
     * @param set_z The new Z-coordinate to be set.
     * @return Reference to the updated Point object.
     */
    Point& setZ(double set_z) { this->z = set_z; return *this; }
};

#endif //GRAYVE_POINT_H
