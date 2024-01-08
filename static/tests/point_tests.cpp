#include "catch.hpp"
#include "point.h"

// Test cases for the Point class
TEST_CASE("Point Class", "Point") {
    // Test default constructor
    SECTION("Default Constructor") {
        Point point;
        REQUIRE(point.getX() == 0.0);
        REQUIRE(point.getZ() == 0.0);
    }

        // Test parameterized constructor
    SECTION("Parameterized Constructor") {
        Point point(3.5, 2.0);
        REQUIRE(point.getX() == 3.5);
        REQUIRE(point.getZ() == 2.0);
    }

        // Test getter methods
    SECTION("Getter Methods") {
        Point point(1.5, 4.0);
        REQUIRE(point.getX() == 1.5);
        REQUIRE(point.getZ() == 4.0);
    }

        // Test setter methods
    SECTION("Setter Methods") {
        Point point;
        point.setX(2.0).setZ(5.5);
        REQUIRE(point.getX() == 2.0);
        REQUIRE(point.getZ() == 5.5);
    }
}
