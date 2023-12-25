#ifndef GRAYVE_PROJECTILE_H
#define GRAYVE_PROJECTILE_H
#include "entity.h"

class Projectile: public Entity {
    int update_count;
    int damage;
    EntityType creator_type;
public:
    [[nodiscard]] virtual EntityType get_entity_type() const;
    Projectile(field::Map *map, double phi, Point point, EntityType creator_type) : Entity(map), update_count(0), creator_type(creator_type){
        this->setPhi(phi);
        this->setCoordinates(point);
        this->setMoveForward(true);
        this->setSpeed(4./20);
    }
    Projectile(field::Map *map) : Projectile(map, 0, Point(0, 0), EntityType::DEFAULT) {}
    void update() override;
};

#endif //GRAYVE_PROJECTILE_H
