#include "catch.hpp"
#include "chunk.h"

TEST_CASE("Default Constructor", "Chunk") {
    field::Chunk chunk;
    REQUIRE(chunk.left_bottom.getX() == 0.0);
    REQUIRE(chunk.left_bottom.getZ() == 0.0);
    REQUIRE(chunk.right_top.getX() == 0.0);
    REQUIRE(chunk.right_top.getZ() == 0.0);
    REQUIRE(chunk.room == nullptr);
}

TEST_CASE("Generate Room Method") {
    field::Chunk chunk;
    chunk.generate_room();
    REQUIRE(chunk.room != nullptr);

    SECTION("Room Dimensions") {
        REQUIRE(chunk.right_top.getX() >= chunk.left_bottom.getX());
        REQUIRE(chunk.right_top.getZ() >= chunk.left_bottom.getZ());
    }

    SECTION("Specific Blocks") {
        Block& block = chunk.get_block(chunk.left_bottom.getX(), chunk.left_bottom.getZ());
        REQUIRE(block.get_block_type() == Tile::Wall);

        block = chunk.get_block(chunk.right_top.getX(), chunk.right_top.getZ());
        REQUIRE(block.get_block_type() == Tile::Wall);
    }
}

TEST_CASE("Copy Constructor", "Chunk") {
    field::Chunk originalChunk;
    originalChunk.generate_room();

    field::Chunk copiedChunk(originalChunk);
    REQUIRE(copiedChunk.left_bottom.getX() == originalChunk.left_bottom.getX());
    REQUIRE(copiedChunk.left_bottom.getZ() == originalChunk.left_bottom.getZ());
    REQUIRE(copiedChunk.right_top.getX() == originalChunk.right_top.getX());
    REQUIRE(copiedChunk.right_top.getZ() == originalChunk.right_top.getZ());

    for (unsigned int y = 0; y < field::CHUNK_SIZE; ++y)
        for (unsigned int x = 0; x < field::CHUNK_SIZE; ++x)
            REQUIRE(copiedChunk.room[y][x].get_block_type() == originalChunk.room[y][x].get_block_type());
}

TEST_CASE("Move Constructor", "Chunk") {
    field::Chunk originalChunk;
    originalChunk.generate_room();

    field::Chunk movedChunk(std::move(originalChunk));
    REQUIRE(movedChunk.left_bottom.getX() == originalChunk.left_bottom.getX());
    REQUIRE(movedChunk.left_bottom.getZ() == originalChunk.left_bottom.getZ());
    REQUIRE(movedChunk.right_top.getX() == originalChunk.right_top.getX());
    REQUIRE(movedChunk.right_top.getZ() == originalChunk.right_top.getZ());
}

TEST_CASE("Copy Assignment Operator") {
    field::Chunk originalChunk;
    originalChunk.generate_room();

    field::Chunk copiedChunk;
    copiedChunk = originalChunk;
    REQUIRE(copiedChunk.left_bottom.getX() == originalChunk.left_bottom.getX());
    REQUIRE(copiedChunk.left_bottom.getZ() == originalChunk.left_bottom.getZ());
    REQUIRE(copiedChunk.right_top.getX() == originalChunk.right_top.getX());
    REQUIRE(copiedChunk.right_top.getZ() == originalChunk.right_top.getZ());

    for (unsigned int y = 0; y < field::CHUNK_SIZE; ++y)
        for (unsigned int x = 0; x < field::CHUNK_SIZE; ++x)
            REQUIRE(copiedChunk.room[y][x].get_block_type() == originalChunk.room[y][x].get_block_type());
}

TEST_CASE("Move Assignment Operator", "Chunk") {
    field::Chunk originalChunk;
    originalChunk.generate_room();

    field::Chunk movedChunk;
    movedChunk = std::move(originalChunk);
    REQUIRE(movedChunk.left_bottom.getX() == originalChunk.left_bottom.getX());
    REQUIRE(movedChunk.left_bottom.getZ() == originalChunk.left_bottom.getZ());
    REQUIRE(movedChunk.right_top.getX() == originalChunk.right_top.getX());
    REQUIRE(movedChunk.right_top.getZ() == originalChunk.right_top.getZ());
}
