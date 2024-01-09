#ifndef GRAYVE_CHARACTER_H
#define GRAYVE_CHARACTER_H

#include "entity.h"
#define SHOOT_COOLDOWN 10

/**
 * @class Character
 * @brief Abstract base class representing a character in the game.
 * @details This class inherits from Entity and serves as a base for various character types.
 */
class Character : public Entity {
protected:
    int health_points; /**< The health points of the character. */
    int shoot_cooldown{}; /**< Cooldown for shooting abilities. */

public:
    /**
     * @brief Virtual function representing the death of the character.
     * @details This function must be implemented in derived classes to handle character death.
     */
    virtual void die();

    /**
     * @brief Pure virtual function to receive damage by the character.
     * @param amount The amount of damage received.
     * @details This function must be implemented in derived classes to handle damage reception.
     */
    virtual void receive_damage(int amount) = 0;

    /**
     * @brief Updates the character's state.
     * @details Overrides the update function from the Entity base class.
     */
    void update() override;

    /**
     * @brief Performs shooting action.
     */
    void shoot();

    /**
     * @brief Default constructor for Character class.
     */
    Character() : Character(nullptr, 10) {}

    /**
     * @brief Parameterized constructor for Character class.
     * @param health_points The initial health points of the character.
     */
    explicit Character(int health_points) : Character(nullptr, health_points) {}

    /**
     * @brief Parameterized constructor for Character class.
     * @param map The map on which the character exists.
     */
    explicit Character(field::Map* map) : Character(map, 0) {}

    /**
     * @brief Parameterized constructor for Character class.
     * @param map The map on which the character exists.
     * @param health_points The initial health points of the character.
     */
    Character(field::Map* map, int health_points) : Entity(map), health_points(health_points) {}

    Character(field::Map* map, int health_points, int chunk_x, int chunk_y) : Entity(map, chunk_x, chunk_y), health_points(health_points) {}
};

#endif //GRAYVE_CHARACTER_H
