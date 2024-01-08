#ifndef GRAYVE_COLLIDER_H
#define GRAYVE_COLLIDER_H

#include "block.h"

/**
 * @class Cylinder
 * @brief Represents a cylinder collider.
 */
class Cylinder {
protected:
    Point* center; /**< Pointer to the center of the cylinder. */
    double radius; /**< Radius of the cylinder. */

public:
    /**
     * @brief Default constructor for Cylinder class.
     */
    Cylinder() : center(nullptr), radius(0) {}

    /**
     * @brief Parameterized constructor for Cylinder class.
     * @param point Pointer to the center point of the cylinder.
     */
    explicit Cylinder(Point* point) : center(point), radius(0) {}

    /**
     * @brief Parameterized constructor for Cylinder class.
     * @param point Pointer to the center point of the cylinder.
     * @param radius The radius of the cylinder.
     */
    Cylinder(Point* point, double radius) : center(point), radius(radius) {}

    /**
     * @brief Destructor for Cylinder class.
     */
    ~Cylinder() {}
};

/**
 * @class ColliderBox
 * @brief Represents a collider box inheriting from Cylinder.
 */
class ColliderBox : public Cylinder {
public:
    /**
     * @brief Checks for intersection with another ColliderBox.
     * @param other The other ColliderBox for intersection check.
     * @return True if there is an intersection, false otherwise.
     */
    [[nodiscard]] bool is_intersect(ColliderBox& other) const;

    /**
     * @brief Checks for intersection with a Block.
     * @param other The Block for intersection check.
     * @return True if there is an intersection, false otherwise.
     */
    [[nodiscard]] bool is_intersect(const Block& other) const;

    /**
     * @brief Default constructor for ColliderBox class.
     */
    ColliderBox() : Cylinder() {}

    /**
     * @brief Parameterized constructor for ColliderBox class.
     * @param point Pointer to the center point of the ColliderBox.
     */
    explicit ColliderBox(Point* point) : Cylinder(point) {}

    /**
     * @brief Parameterized constructor for ColliderBox class.
     * @param point Pointer to the center point of the ColliderBox.
     * @param radius The radius of the ColliderBox.
     */
    ColliderBox(Point* point, double radius) : Cylinder(point, radius) {}

    /**
     * @brief Sets the center point of the ColliderBox.
     * @param point Pointer to the new center point.
     */
    void set_center(Point* point) { this->center = point; }

    /**
     * @brief Sets the radius of the ColliderBox.
     * @param radius The new radius value.
     */
    void set_radius(double radius) { this->radius = radius; }
};

#endif //GRAYVE_COLLIDER_H
