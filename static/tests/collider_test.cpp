#include "catch.hpp"
#include "collider.h"

TEST_CASE("ColliderBox intersect with Block", "ColliderBox") {
    SECTION("ColliderBox intersects with Wall Block") {
        Point centerPoint(5.0, 5.0);
        ColliderBox colliderBox(&centerPoint, 2.0);
        Block wallBlock(Tile::Wall, Point(3.0, 3.0), Point(7.0, 7.0));
        REQUIRE(colliderBox.is_intersect(wallBlock) == true);
    }

    SECTION("ColliderBox non-intersects with Wall Block") {
        Point centerPoint(5.0, 5.0);
        ColliderBox colliderBox(&centerPoint, 2.0);
        Block wallBlock(Tile::Wall, Point(1.0, 1.0), Point(2.0, 2.0));
        REQUIRE(colliderBox.is_intersect(wallBlock) == false);
    }
}

TEST_CASE("ColliderBox intersect with another ColliderBox", "ColliderBox") {
    SECTION("ColliderBox intersects with another ColliderBox") {
        Point centerPoint1(0.0, 0.0);
        ColliderBox colliderBox1(&centerPoint1, 3.);

        Point centerPoint2(5.0, 0.0);
        ColliderBox colliderBox2(&centerPoint2, 2.);

        REQUIRE(colliderBox1.is_intersect(colliderBox2) == true);
    }

    SECTION("ColliderBox non-intersects with another ColliderBox") {
        Point centerPoint1(10.0, 10.0);
        ColliderBox colliderBox1(&centerPoint1, 3.0);

        Point centerPoint2(5.0, 5.0);
        ColliderBox colliderBox2(&centerPoint2, 2.0);

        REQUIRE(colliderBox1.is_intersect(colliderBox2) == false);
    }
}
