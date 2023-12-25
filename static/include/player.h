#ifndef GRAYVE_PLAYER_H
#define GRAYVE_PLAYER_H
#include "character.h"

class Player: public Character {
public:
    [[nodiscard]] EntityType get_entity_type() const override;
    void die() override;
    void deal_damage(Character&) override;
    void recieve_damage(int amount) override;
    void update() override;
    explicit Player(field::Map *map) : Character(map) {};
};

#endif //GRAYVE_PLAYER_H
