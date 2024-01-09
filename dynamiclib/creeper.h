#ifndef GRAYVE_CREEPER_H
#define GRAYVE_CREEPER_H
#include "enemy.h"
#define EXPLOSION_TIMER 10

class Creeper: public Enemy {
private:
    int explosion_timer{10};
public:
    void die() override;
    void update() override;
    [[nodiscard]] std::string get_entity_name() const override;

    explicit Creeper(field::Map* map) : Enemy(map, 10) {};

    Creeper(field::Map* map, int health_points) : Enemy(map, health_points) {};

    Creeper(field::Map* map, int chunk_x, int chunk_y) : Enemy(map, 10, chunk_x, chunk_y) {};

    Creeper(field::Map* map, int health_points, int chunk_x, int chunk_y)
        : Enemy(map, health_points, chunk_x, chunk_y) {};
};

#endif //GRAYVE_CREEPER_H
