#ifndef GRAYVE_ENEMY_H
#define GRAYVE_ENEMY_H

#define SHOOT_COOLDOWN 10
#include "character.h"

/**
 * @class Enemy
 * @brief Represents an enemy character within the game.
 */
class Enemy : public Character {
protected:
    Entity* follow{}; /**< Entity that the enemy is following. */

public:
    /**
     * @brief Gets the entity type of the Enemy.
     * @return The entity type of the Enemy.
     */
    [[nodiscard]] EntityType get_entity_type() const override;

    [[nodiscard]] std::string get_entity_name() const override;

    /**
     * @brief Handles the death of the Enemy.
     */
    void die() override {Character::die();};

    /**
     * @brief Receives damage by the Enemy.
     * @param amount The amount of damage received.
     */
    void receive_damage(int amount) override {Character::receive_damage(amount);};

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

    Enemy(field::Map* map, int health_points) : Character(map, health_points) {};

    Enemy(field::Map* map, int chunk_x, int chunk_y) : Character(map, 5, chunk_x, chunk_y) {};

    Enemy(field::Map* map, int health_points, int chunk_x, int chunk_y) : Character(map, health_points, chunk_x, chunk_y) {};
};

#endif //GRAYVE_ENEMY_H
