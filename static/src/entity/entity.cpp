#include "entity.h"

void Entity::update_position() {
    if (!this->isMoving()) return;
    double dx = 0, dz = 0;
    if (this->move_forward) {
        dx += cos(this->phi) * this->speed;
        dz += sin(this->phi) * this->speed;
    }
    if (this->move_backward) {
        dx -= cos(this->phi) * this->speed;
        dz -= sin(this->phi) * this->speed;
    }
    if (this->move_left) {
        dx -= (cos(this->phi + M_PI_2) * this->speed);
        dz -= (sin(this->phi + M_PI_2) * this->speed);
    }
    if (this->move_right) {
        dx -= (cos(this->phi - M_PI_2) * this->speed);
        dz -= (sin(this->phi - M_PI_2) * this->speed);
    }
    if (dx == 0 && dz == 0) return;

    double current_x = this->coordinates.getX();
    double current_z = this->coordinates.getZ();
    double dest_x = current_x + dx;
    double dest_z = current_z + dz;

    if (!this->is_wall_colliding(dest_x, current_z)) {
        this->lock_dx = false;
        this->coordinates.setX(dest_x);
    } else
        this->lock_dx = true;


    if (!this->is_wall_colliding(current_x, dest_z)) {
        this->lock_dz = false;
        this->coordinates.setZ(dest_z);
    } else
        this->lock_dz = true;
}

bool Entity::is_wall_colliding(double dest_x, double dest_z) {
    double current_x = this->coordinates.getX();
    double current_z = this->coordinates.getZ();
    const field::Chunk &current_chunk = this->globalMap->get_chunk(this->chunk_x, this->chunk_y);
    const Block blocks[9] = {current_chunk.get_block(current_x + 1, current_z),
                             current_chunk.get_block(current_x, current_z + 1),
                             current_chunk.get_block(current_x - 1, current_z),
                             current_chunk.get_block(current_x, current_z - 1),
                             current_chunk.get_block(current_x + 1, current_z + 1),
                             current_chunk.get_block(current_x + 1, current_z - 1),
                             current_chunk.get_block(current_x - 1, current_z + 1),
                             current_chunk.get_block(current_x - 1, current_z - 1),
                             current_chunk.get_block(current_x, current_z)};

    this->coordinates.setX(dest_x);
    this->coordinates.setZ(dest_z);
    bool intersect = false;
    for (auto i: blocks)
        intersect += this->collider.is_intersect(i);
    this->coordinates.setX(current_x);
    this->coordinates.setZ(current_z);
    return intersect;
}

bool Entity::isMoving() const {
    return bool(this->move_right || this->move_left || this->move_backward || this->move_forward);
}

void Entity::setCoordinates(Point point) {
    this->coordinates = point;
    this->collider.set_center(&(this->coordinates));
    this->collider.set_radius(0.25);
}

double Entity::get_interpolatedX(double interpolation) const {
    if (!this->isMoving()) return this->coordinates.getX();
    if (this->lock_dx) return this->coordinates.getX();
    double dx = 0;
    if (move_forward)
        dx += cos(this->phi) * this->speed * interpolation;
    if (move_backward)
        dx -= cos(this->phi) * this->speed * interpolation;
    if (move_right)
        dx -= cos(this->phi - M_PI_2) * this->speed * interpolation;
    if (move_left)
        dx -= cos(this->phi + M_PI_2) * this->speed * interpolation;
    return this->coordinates.getX() + dx;
}

double Entity::get_interpolatedZ(double interpolation) const {
    if (!this->isMoving()) return this->coordinates.getZ();
    if (this->lock_dz) return this->coordinates.getZ();
    double dz = 0;
    if (move_forward)
        dz += sin(this->phi) * this->speed * interpolation;
    if (move_backward)
        dz -= sin(this->phi) * this->speed * interpolation;
    if (move_right)
        dz -= sin(this->phi - M_PI_2) * this->speed * interpolation;
    if (move_left)
        dz -= sin(this->phi + M_PI_2) * this->speed * interpolation;
    return this->coordinates.getZ() + dz;
}

void Entity::update() {
    this->update_position();
}

Entity::~Entity() {
    this->globalMap->remove_entity(this);
}

Entity::Entity(field::Map *map) : globalMap(map) {
    this->collider = ColliderBox(&this->coordinates, 0.5);
    if (map)
        map->add_entity(this);
    this->chunk_x = 5;
    this->chunk_y = 5;
}

Entity::Entity(field::Map *map, int chunk_x, int chunk_y) : globalMap(map) {
    this->collider = ColliderBox(&this->coordinates, 0.5);
    if (map)
        map->add_entity(this);
    this->chunk_x = chunk_x;
    this->chunk_y = chunk_y;
}

ColliderBox &Entity::get_collider() {
    return this->collider;
}

bool Entity::isSameChunk(Entity &other) const {
    return (this->chunk_x == other.chunk_x) && (this->chunk_y == other.chunk_y);
}