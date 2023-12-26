#ifndef GRAYVE_ENEMY_H
#define GRAYVE_ENEMY_H
#include "character.h"

class Enemy: public Character {
private:
    Entity *follow{};
public:
    [[nodiscard]] EntityType get_entity_type() const override;
    void die() override {};
    void deal_damage(Character&) override {};
    void receive_damage(int amount) override {};
    void update() override;
    void set_follow(Entity *set) {this->follow = set;}
    explicit Enemy(field::Map *map) : Character(map, 5) {};
};

#endif //GRAYVE_ENEMY_H
