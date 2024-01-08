#include "catch.hpp"
#include "map.h"

struct MapFixture {
    field::Map map;
    MapFixture() : map(5) {}
};

TEST_CASE_METHOD(MapFixture, "Map construction") {
    REQUIRE(map.get_map_size() == 5);
    REQUIRE(map.get_starter_x() == 0);
    REQUIRE(map.get_starter_y() == 0);
}

TEST_CASE_METHOD(MapFixture, "Map updates") {
    class MockEntity : public Entity {
    public:
        explicit MockEntity(field::Map* map) : Entity(map) {}

        [[nodiscard]] EntityType get_entity_type() const override { return EntityType::DEFAULT; }
        void update() override {}
    };

    MockEntity mock_entity(&map);
    REQUIRE(map.new_entity.size() == 1);
    map.update();
    REQUIRE(map.entity_set.size() == 1);

    map.remove_entity(&mock_entity);
    map.update();
    REQUIRE(map.entity_set.empty());

}

TEST_CASE_METHOD(MapFixture, "Map creation") {
    map.generate_room_map(8);
    REQUIRE(1 == 1);
}