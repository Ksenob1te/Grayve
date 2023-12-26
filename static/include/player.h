#ifndef GRAYVE_PLAYER_H
#define GRAYVE_PLAYER_H
#include "character.h"
#define SHOOT_COOLDOWN 15
#define SPRINT_COOLDOWN 50
#define SPRINT_LENGTH 20
#define DEFAULT_SPEED (1./10)

class Player: public Character {
private:
    bool shoot_action{}, sprint_action{};
    int shoot_cooldown{}, sprint_cooldown{}, sprint_length{};

public:
    [[nodiscard]] EntityType get_entity_type() const override;
    void die() override;
    void deal_damage(Character&) override;
    void recieve_damage(int amount) override;
    void update() override;
    explicit Player(field::Map *map) : Character(map) {};

    void set_shoot_action(bool state) {this->shoot_action = state;}
    void set_sprint(bool state) {this->sprint_action = state;}
};

#endif //GRAYVE_PLAYER_H
