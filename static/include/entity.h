#ifndef GRAYVE_ENTITY_H
#define GRAYVE_ENTITY_H
#include "cmath"
#include "point.h"
#include "collider.h"
#include "map.h"

namespace field {
    class Map;
}

enum class EntityType {
    DEFAULT,
    PLAYER,
    ENEMY,
    PROJECTILE
};

class Entity {
protected:
    Point coordinates;
    double height{};
    double phi{};
    double speed{};
    bool move_left{}, move_right{}, move_forward{}, move_backward{};
    ColliderBox collider;
    bool lock_dx{}, lock_dz{};
    field::Map *globalMap;

public:
    virtual void update() = 0;
    [[nodiscard]] virtual EntityType get_entity_type() const = 0;

    [[nodiscard]] double getX() const {return coordinates.getX();}
    [[nodiscard]] double getY() const {return height;}
    [[nodiscard]] double getZ() const {return coordinates.getZ();}
    [[nodiscard]] double getPhi() const {return phi;}
    [[nodiscard]] double getSpeed() const {return speed;}
    [[nodiscard]] double get_interpolatedX(double interpolation) const;
    [[nodiscard]] double get_interpolatedZ(double interpolation) const;
    void setCoordinates(Point point);
    void setHeight(double new_height) {this->height = new_height;}
    void update_position();

    Entity* setMoveLeft(bool state) {move_left = state; return this;}
    Entity* setMoveRight(bool state) {move_right = state; return this;}
    Entity* setMoveForward(bool state) {move_forward = state; return this;}
    Entity* setMoveBackward(bool state) {move_backward = state; return this;}

    ColliderBox& get_collider();

    void setSpeed(double set_speed) {this->speed = std::abs(set_speed);}
    void setPhi(double set_phi) {
        while (set_phi < -M_PI) set_phi += (2 * M_PI);
        while (set_phi > M_PI) set_phi -= (2 * M_PI);
        this->phi = set_phi;
    }

    [[nodiscard]] bool is_wall_colliding(double dest_x, double dest_z);
    [[nodiscard]] bool isMoving() const;

    Entity(): Entity(nullptr) {};
    explicit Entity(field::Map *map);
    virtual ~Entity();
};

#endif //GRAYVE_ENTITY_H
