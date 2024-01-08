#ifndef GRAYVE_ENEMY_H
#define GRAYVE_ENEMY_H

#include "character.h"

/**
 * @class Enemy
 * @brief Represents an enemy character within the game.
 */
class Enemy : public Character {
private:
    Entity* follow; /**< Entity that the enemy is following. */

public:
    /**
     * @brief Gets the entity type of the Enemy.
     * @return The entity type of the Enemy.
     */
    [[nodiscard]] EntityType get_entity_type() const override;

    /**
     * @brief Handles the death of the Enemy.
     */
    void die() override {};

    /**
     * @brief Receives damage by the Enemy.
     * @param amount The amount of damage received.
     */
    void receive_damage(int amount) override {};

    /**
     * @brief Updates the state of the Enemy.
     */
    void update() override;

    /**
     * @brief Sets the Entity that the Enemy follows.
     * @param set The Entity to be followed.
     */
    void set_follow(Entity* set) { this->follow = set; }

    /**
     * @brief Parameterized constructor for Enemy class.
     * @param map The map on which the Enemy exists.
     */
    explicit Enemy(field::Map* map) : Character(map, 5) {};
};

#endif //GRAYVE_ENEMY_H
