#ifndef GRAYVE_ENTITY_H
#define GRAYVE_ENTITY_H

#include "cmath"
#include "point.h"
#include "collider.h"
#include "map.h"

namespace field {
    class Map;
}

enum class EntityType {
    DEFAULT,
    PLAYER,
    ENEMY,
    PROJECTILE
};

/**
 * @class Entity
 * @brief Represents an entity within the game.
 */
class Entity {
protected:
    Point coordinates; /**< Coordinates of the entity. */
    double height{}; /**< Height of the entity. */
    double phi{}; /**< Angle of rotation of the entity. */
    double speed{}; /**< Speed of the entity. */
    bool move_left{}, move_right{}, move_forward{}, move_backward{}; /**< Movement flags for the entity. */
    ColliderBox collider; /**< Collider box for collision detection. */
    bool lock_dx{}, lock_dz{}; /**< Flags to lock movement in X and Z axes. */
    field::Map* globalMap; /**< Pointer to the global map. */

public:
    /**
     * @brief Default constructor for Entity class.
     * @details Initializes the entity with a nullptr map.
     */
    Entity(): Entity(nullptr) {};

    /**
     * @brief Parameterized constructor for Entity class.
     * @param map The map on which the Entity exists.
     */
    explicit Entity(field::Map* map);

    /**
     * @brief Destructor for Entity class.
     * @details Cleans up resources allocated for the entity.
     */
    virtual ~Entity();

    /**
     * @brief Updates the state of the entity.
     */
    virtual void update() = 0;

    /**
     * @brief Gets the entity type.
     * @return The type of entity.
     */
    [[nodiscard]] virtual EntityType get_entity_type() const = 0;

    // Getter methods

    /**
     * @brief Gets the X coordinate of the entity.
     * @return The X coordinate.
     */
    [[nodiscard]] double getX() const { return coordinates.getX(); }

    /**
     * @brief Gets the Y coordinate of the entity.
     * @return The Y coordinate.
     */
    [[nodiscard]] double getY() const { return height; }

    /**
     * @brief Gets the Z coordinate of the entity.
     * @return The Z coordinate.
     */
    [[nodiscard]] double getZ() const { return coordinates.getZ(); }

    /**
     * @brief Gets the rotation angle (phi) of the entity.
     * @return The rotation angle.
     */
    [[nodiscard]] double getPhi() const { return phi; }

    /**
     * @brief Gets the speed of the entity.
     * @return The speed value.
     */
    [[nodiscard]] double getSpeed() const { return speed; }

    /**
     * @brief Gets the interpolated X coordinate of the entity.
     * @param interpolation The interpolation factor.
     * @return The interpolated X coordinate.
     */
    [[nodiscard]] double get_interpolatedX(double interpolation) const;

    /**
     * @brief Gets the interpolated Z coordinate of the entity.
     * @param interpolation The interpolation factor.
     * @return The interpolated Z coordinate.
     */
    [[nodiscard]] double get_interpolatedZ(double interpolation) const;

    /**
     * @brief Gets the collider box of the entity.
     * @return Reference to the collider box.
     */
    ColliderBox& get_collider();

    // Setter methods

    /**
     * @brief Sets the coordinates of the entity.
     * @param point The new coordinates.
     */
    void setCoordinates(Point point);

    /**
     * @brief Sets the height of the entity.
     * @param new_height The new height value.
     */
    void setHeight(double new_height) { this->height = new_height; }

    /**
     * @brief Updates the position of the entity.
     */
    void update_position();

    /**
     * @brief Sets the flag for left movement.
     * @param state The state of left movement.
     * @return The updated Entity object.
     */
    Entity* setMoveLeft(bool state) { move_left = state; return this; }

    /**
     * @brief Sets the flag for right movement.
     * @param state The state of right movement.
     * @return The updated Entity object.
     */
    Entity* setMoveRight(bool state) { move_right = state; return this; }

    /**
     * @brief Sets the flag for forward movement.
     * @param state The state of forward movement.
     * @return The updated Entity object.
     */
    Entity* setMoveForward(bool state) { move_forward = state; return this; }

    /**
     * @brief Sets the flag for backward movement.
     * @param state The state of backward movement.
     * @return The updated Entity object.
     */
    Entity* setMoveBackward(bool state) { move_backward = state; return this; }

    /**
     * @brief Sets the speed of the entity.
     * @param set_speed The speed value to be set.
     */
    void setSpeed(double set_speed) { this->speed = std::abs(set_speed); }

    /**
     * @brief Sets the rotation angle (phi) of the entity.
     * @param set_phi The phi value to be set.
     */
    void setPhi(double set_phi) {
        while (set_phi < -M_PI) set_phi += (2 * M_PI);
        while (set_phi > M_PI) set_phi -= (2 * M_PI);
        this->phi = set_phi;
    };

    // Additional methods

    /**
     * @brief Checks if the entity is colliding with a wall.
     * @param dest_x Destination X coordinate.
     * @param dest_z Destination Z coordinate.
     * @return True if colliding with a wall, else false.
     */
    [[nodiscard]] bool is_wall_colliding(double dest_x, double dest_z);

    /**
     * @brief Checks if the entity is moving.
     * @return True if the entity is moving, else false.
     */
    [[nodiscard]] bool isMoving() const;
};

#endif //GRAYVE_ENTITY_H
