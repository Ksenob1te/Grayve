#ifndef GRAYVE_BLOCK_H
#define GRAYVE_BLOCK_H
#include "point.h"
#include "iostream"

enum class Tile {
    Void,
    Floor,
    Wall,
    Small_Wall
};

class Block {
public:
    Tile block_type;
    Point left_bottom;
    Point right_top;

public:
    Block(): block_type(Tile::Void) {};
    explicit Block(Tile set_block): block_type(set_block) {};

    Block(Tile set_block, Point left_bottom, Point right_top) :
            block_type(set_block), left_bottom(left_bottom), right_top(right_top) {};

    void set_block_type(Tile set_block) {this->block_type = set_block;};
    void set_left_bottom(Point &set_left_bottom) {this->left_bottom = set_left_bottom;};
    void set_right_top(Point &set_right_top) {this->right_top = set_right_top;};

    [[nodiscard]] Tile get_block_type() const {return block_type;};
    [[nodiscard]] const Point& get_left_bottom() const {return left_bottom;};
    [[nodiscard]] const Point& get_right_top() const {return right_top;};

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
