#ifndef GRAYVE_PROJECTILE_H
#define GRAYVE_PROJECTILE_H

#include "entity.h"

/**
 * @class Projectile
 * @brief Represents a projectile fired within the game.
 */
class Projectile: public Entity {
    int life_time; /**< Lifetime of the projectile. */
    int damage; /**< Damage caused by the projectile. */
    EntityType creator_type; /**< Type of the entity that created the projectile. */

public:
    /**
     * @brief Gets the entity type of the Projectile.
     * @return The entity type of the Projectile.
     */
    [[nodiscard]] EntityType get_entity_type() const override;

    /**
     * @brief Parameterized constructor for Projectile class.
     * @param map The map on which the Projectile exists.
     * @param phi The angle of the Projectile.
     * @param point The starting Point of the Projectile.
     * @param creator_type The type of entity that created the Projectile.
     */

    Projectile(field::Map *map, double phi, Point point, EntityType creator_type, int chunk_x, int chunk_y)
            : Entity(map, chunk_x, chunk_y), life_time(0), creator_type(creator_type), damage(1) {
        this->setPhi(phi);
        this->setCoordinates(point);
        this->collider.set_radius(0.1);
        this->setMoveForward(true);
        this->setSpeed(8.0 / 20.0);
    }

    Projectile(field::Map *map, double phi, Point point, EntityType creator_type)
            : Projectile(map, phi, point, creator_type, 0, 0) {}

    /**
     * @brief Default constructor for Projectile class.
     * @param map The map on which the Projectile exists.
     */
    explicit Projectile(field::Map *map) : Projectile(map, 0, Point(0, 0), EntityType::DEFAULT) {}

    /**
     * @brief Destructor for Projectile class.
     * @details Cleans up resources allocated for the Projectile.
     */
    ~Projectile();

    /**
     * @brief Updates the state of the Projectile.
     */
    void update() override;
};

#endif //GRAYVE_PROJECTILE_H
