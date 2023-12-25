#ifndef GRAYVE_CHARACTER_H
#define GRAYVE_CHARACTER_H
#include "entity.h"

class Character: public Entity {
private:
    int health_points;
public:
    virtual void die() {};
    virtual void deal_damage(Character&) {};
    virtual void recieve_damage(int amount) {};
    Character() : Character(nullptr, 0) {};
    explicit Character(int health_points) : Character(nullptr, health_points) {};
    explicit Character(field::Map *map) : Character(map, 0) {};
    Character(field::Map *map, int health_points) : Entity(map), health_points(health_points) {};
    ~Character() = default;
};

#endif //GRAYVE_CHARACTER_H
