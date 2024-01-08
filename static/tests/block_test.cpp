#include "catch.hpp"
#include "block.h"
#include "string"
#include "sstream"

TEST_CASE("Block Constructors", "Block") {
    // Default constructor test
    SECTION("Default Constructor") {
        Block block;
        REQUIRE(block.get_block_type() == Tile::Void);
        // Ensure default values for coordinates are (0,0)
        REQUIRE(block.get_left_bottom().getX() == 0);
        REQUIRE(block.get_left_bottom().getZ() == 0);
        REQUIRE(block.get_right_top().getX() == 0);
        REQUIRE(block.get_right_top().getZ() == 0);
    }

        // Parameterized constructor test
    SECTION("Parameterized Constructors") {
        // Test with different block types and coordinates
        Block floorBlock(Tile::Floor);
        REQUIRE(floorBlock.get_block_type() == Tile::Floor);

        Point leftBottom(1.0, 3.0);
        Point rightTop(4.0, 6.0);
        Block wallBlock(Tile::Wall, leftBottom, rightTop);

        REQUIRE(wallBlock.get_block_type() == Tile::Wall);
        REQUIRE(wallBlock.get_left_bottom().getX() == 1.0);
        REQUIRE(wallBlock.get_left_bottom().getZ() == 3.0);
        REQUIRE(wallBlock.get_right_top().getX() == 4.0);
        REQUIRE(wallBlock.get_right_top().getZ() == 6.0);
    }
}

// Test cases for setter and getter methods
TEST_CASE("Setter and Getter Methods", "Block") {
    Block block;

    // Setter methods test
    SECTION("Setter Methods") {
        block.set_block_type(Tile::Floor);
        REQUIRE(block.get_block_type() == Tile::Floor);

        Point newLeftBottom(1.0, 3.0);
        block.set_left_bottom(newLeftBottom);
        REQUIRE(block.get_left_bottom().getX() == 1.0);
        REQUIRE(block.get_left_bottom().getZ() == 3.0);

        Point newRightTop(4.0, 6.0);
        block.set_right_top(newRightTop);
        REQUIRE(block.get_right_top().getX() == 4.0);
        REQUIRE(block.get_right_top().getZ() == 6.0);
    }

        // Getter methods test
    SECTION("Getter Methods") {
        // Ensure default values are returned for an uninitialized block
        REQUIRE(block.get_block_type() == Tile::Void);
        REQUIRE(block.get_left_bottom().getX() == 0);
        REQUIRE(block.get_left_bottom().getZ() == 0);
        REQUIRE(block.get_right_top().getX() == 0);
        REQUIRE(block.get_right_top().getZ() == 0);
    }
}

// Test cases for calculation methods
TEST_CASE("Calculation Methods", "Block") {
    // Test case for block center calculations
    SECTION("Block Center Calculations") {
        Point leftBottom(1.0, 1.0);
        Point rightTop(5.0, 5.0);
        Block block(Tile::Floor, leftBottom, rightTop);

        REQUIRE(block.centerX() == 3.0);
        REQUIRE(block.centerZ() == 3.0);
    }

        // Test case for block side length calculation
    SECTION("Block Side Length Calculation") {
        Point leftBottom(1.0, 1.0);
        Point rightTop(4.0, 4.0);
        Block block(Tile::Floor, leftBottom, rightTop);

        REQUIRE(block.sideLength() == 3.0);
    }
}

// Test case for printing method
TEST_CASE("Printing Method", "Block") {
    // Test print_block() method for different block types
    SECTION("Print Block") {
        Block voidBlock(Tile::Void);
        Block floorBlock(Tile::Floor);
        Block wallBlock(Tile::Wall);
        Block smallWallBlock(Tile::Small_Wall);

        // Redirect cout to a stringstream to capture output
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        voidBlock.print_block();
        floorBlock.print_block();
        wallBlock.print_block();
        smallWallBlock.print_block();

        std::string output = buffer.str();

        // Check the expected output for each block type
        REQUIRE(output == "  . # = ");

        // Restore cout
        std::cout.rdbuf(old);
    }
}

