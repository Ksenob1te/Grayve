#ifndef GRAYVE_PLAYER_H
#define GRAYVE_PLAYER_H

#include "character.h"
#define SPRINT_COOLDOWN 50
#define SPRINT_LENGTH 20
#define DEFAULT_SPEED (1./10)

class Player: public Character {
private:
    bool shoot_action{}; /**< Flag for shooting action. */
    bool sprint_action{}; /**< Flag for sprint action. */
    int sprint_cooldown{}; /**< Cooldown for sprint action. */
    int sprint_length{}; /**< Length of sprint. */

public:
    /**
     * @brief Gets the entity type of the Player.
     * @return The entity type of the Player.
     */
    [[nodiscard]] EntityType get_entity_type() const override;

    [[nodiscard]] std::string get_entity_name() const override;

    /**
     * @brief Handles the death of the Player.
     */
    void die() override;

    /**
     * @brief Receives damage by the Player.
     * @param amount The amount of damage received.
     */
    void receive_damage(int amount) override;

    /**
     * @brief Updates the state of the Player.
     */
    void update() override;

    /**
     * @brief Parameterized constructor for Player class.
     * @param map The map on which the Player exists.
     */
    explicit Player(field::Map* map) : Character(map, 100) {};

    Player(field::Map* map, int chunk_x, int chunk_y) : Character(map, 100, chunk_x, chunk_y) {};

    /**
     * @brief Sets the shoot action for the Player.
     * @param state The state of the shoot action.
     */
    void set_shoot_action(bool state) { this->shoot_action = state; }

    /**
     * @brief Sets the sprint action for the Player.
     * @param state The state of the sprint action.
     */
    void set_sprint(bool state) { this->sprint_action = state; }
};

#endif //GRAYVE_PLAYER_H
