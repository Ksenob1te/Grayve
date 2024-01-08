#ifndef GRAYVE_BLOCK_H
#define GRAYVE_BLOCK_H

#include "point.h"
#include <iostream>

/**
 * @enum Tile
 * @brief Enumerated type representing different block types.
 */
enum class Tile {
    Void,         /**< Represents an empty block. */
    Floor,        /**< Represents a floor block. */
    Wall,         /**< Represents a wall block. */
    Small_Wall    /**< Represents a small wall block. */
};

/**
 * @class Block
 * @brief Class representing a block in a grid-based system.
 */
class Block {
private:
    Tile block_type;    /**< Type of the block. */
    Point left_bottom;  /**< Coordinates of the bottom-left corner of the block. */
    Point right_top;    /**< Coordinates of the top-right corner of the block. */

public:
    /**
     * @brief Default constructor for Block class.
     */
    Block() : block_type(Tile::Void) {}

    /**
     * @brief Parameterized constructor for Block class.
     * @param set_block The type of block to be set.
     */
    explicit Block(Tile set_block) : block_type(set_block) {}

    /**
     * @brief Parameterized constructor for Block class.
     * @param set_block The type of block to be set.
     * @param left_bottom The bottom-left corner coordinates of the block.
     * @param right_top The top-right corner coordinates of the block.
     */
    Block(Tile set_block, Point left_bottom, Point right_top) :
            block_type(set_block), left_bottom(left_bottom), right_top(right_top) {}

    /**
     * @brief Setter for the block type.
     * @param set_block The type of block to be set.
     */
    void set_block_type(Tile set_block) { this->block_type = set_block; }

    /**
     * @brief Setter for the bottom-left corner coordinates of the block.
     * @param set_left_bottom The bottom-left corner coordinates of the block.
     */
    void set_left_bottom(Point& set_left_bottom) { this->left_bottom = set_left_bottom; }

    /**
     * @brief Setter for the top-right corner coordinates of the block.
     * @param set_right_top The top-right corner coordinates of the block.
     */
    void set_right_top(Point& set_right_top) { this->right_top = set_right_top; }

    /**
     * @brief Getter for the block type.
     * @return The type of block.
     */
    [[nodiscard]] Tile get_block_type() const { return block_type; }

    /**
     * @brief Getter for the bottom-left corner coordinates of the block.
     * @return The bottom-left corner coordinates of the block.
     */
    [[nodiscard]] const Point& get_left_bottom() const { return left_bottom; }

    /**
     * @brief Getter for the top-right corner coordinates of the block.
     * @return The top-right corner coordinates of the block.
     */
    [[nodiscard]] const Point& get_right_top() const { return right_top; }

    /**
     * @brief Calculates the X coordinate of the block's center.
     * @return The X coordinate of the block's center.
     */
    [[nodiscard]] double centerX() const { return (this->right_top.getX() + this->left_bottom.getX()) / 2; }

    /**
     * @brief Calculates the Z coordinate of the block's center.
     * @return The Z coordinate of the block's center.
     */
    [[nodiscard]] double centerZ() const { return (this->right_top.getZ() + this->left_bottom.getZ()) / 2; }

    /**
     * @brief Calculates the side length of the block.
     * @return The side length of the block.
     */
    [[nodiscard]] double sideLength() const { return std::abs(this->right_top.getX() - this->left_bottom.getX()); }

    /**
     * @brief Prints the visual representation of the block based on its type.
     */
    void print_block() const {
        switch (block_type) {
            case Tile::Void:
                std::cout << "  ";
                break;
            case Tile::Floor:
                std::cout << ". ";
                break;
            case Tile::Wall:
                std::cout << "# ";
                break;
            case Tile::Small_Wall:
                std::cout << "= ";
                break;
        }
    }
};

#endif //GRAYVE_BLOCK_H
