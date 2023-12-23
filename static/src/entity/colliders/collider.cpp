#include "collider.h"
#include "cmath"

bool ColliderBox::is_intersect(const Block &other) {
    if (other.get_block_type() != Tile::Wall && other.get_block_type() != Tile::Small_Wall) return false;
    double closestX = std::max(other.get_left_bottom().getX(), std::min(this->center->getX(), other.get_right_top().getX()));
    double closestZ = std::max(other.get_left_bottom().getZ(), std::min(this->center->getZ(), other.get_right_top().getZ()));

    double distanceX = this->center->getX() - closestX;
    double distanceZ = this->center->getZ() - closestZ;
    double distanceSquared = (distanceX * distanceX) + (distanceZ * distanceZ);

    return distanceSquared <= (this->radius * this->radius);
}

bool ColliderBox::is_intersect(ColliderBox &other) {
    double distance = sqrt(pow(this->center->getX() - other.center->getX(), 2) + pow(this->center->getZ() - other.center->getZ(), 2));
    return distance <= (this->radius + other.radius);
}