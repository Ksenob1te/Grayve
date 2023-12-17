#include "collider.h"
#include "cmath"

bool ColliderBox::is_intersect(Block &other) {
    float closestX = std::max(other.get_left_bottom().getX(), std::min(this->center->getX(), other.get_right_top().getX()));
    float closestZ = std::max(other.get_left_bottom().getZ(), std::min(this->center->getZ(), other.get_right_top().getZ()));

    float distance = sqrt(pow(this->center->getX() - closestX, 2) + pow(this->center->getZ() - closestZ, 2));

    if (distance <= this->radius) {
        return true;
    }

    double squareCorners[4][2] = {
            { other.get_left_bottom().getX(),   other.get_left_bottom().getZ()  },
            { other.get_right_top().getX(),     other.get_left_bottom().getZ()  },
            { other.get_left_bottom().getX(),   other.get_right_top().getZ()    },
            { other.get_right_top().getX(),     other.get_right_top().getZ()    }
    };

    for (int i = 0; i < 4; ++i) {
        float dx = squareCorners[i][0] - this->center->getX();
        float dy = squareCorners[i][1] - this->center->getX();
        if (sqrt(dx * dx + dy * dy) <= this->radius) {
            return true;
        }
    }
    return false;
}

bool ColliderBox::is_intersect(ColliderBox &other) {
    float distance = sqrt(pow(this->center->getX() - other.center->getX(), 2) + pow(this->center->getZ() - other.center->getZ(), 2));
    return distance <= (this->radius + other.radius);
}