#ifndef GRAYVE_PROJECTILE_H
#define GRAYVE_PROJECTILE_H
#include "entity.h"

class Projectile: public Entity {
    int life_time;
    int damage;
    EntityType creator_type;
public:
    [[nodiscard]] EntityType get_entity_type() const override;
    Projectile(field::Map *map, double phi, Point point, EntityType creator_type)
        : Entity(map), life_time(0), creator_type(creator_type), damage(1) {
        this->setPhi(phi);
        this->setCoordinates(point);
        this->collider.set_radius(0);
        this->setMoveForward(true);
        this->setSpeed(8./20);
    }
    explicit Projectile(field::Map *map) : Projectile(map, 0, Point(0, 0), EntityType::DEFAULT) {}

    void update() override;
};

#endif //GRAYVE_PROJECTILE_H
