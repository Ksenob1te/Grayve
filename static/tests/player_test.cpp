#include "catch.hpp"
#include "player.h" // Include the header for Player class

TEST_CASE("Player class tests", "Player") {
    SECTION("Inherited functionality from Character") {
        field::Map map(10);
        map.generate_room_map(10);
        Player player(&map);

        REQUIRE(player.get_entity_type() == EntityType::PLAYER);
        REQUIRE(player.getY() == Approx(0.0));
        REQUIRE(player.getSpeed() == 0.0);
        REQUIRE(player.getPhi() == 0.0);
        REQUIRE(player.isMoving() == false);

        player.setMoveForward(true);
        REQUIRE(player.isMoving() == true);

        REQUIRE(player.is_wall_colliding(1.0, 1.0) == true);
    }

    SECTION("Inherited functionality from Entity") {
        field::Map map(10);
        map.generate_room_map(10);
        Player player(&map);

        REQUIRE(player.get_collider().is_intersect(Block(Tile::Wall, Point(0, 0), Point(1, 1))) == true);
        REQUIRE(player.isMoving() == false);

        player.update();
        REQUIRE(player.isMoving() == false);
    }
}
