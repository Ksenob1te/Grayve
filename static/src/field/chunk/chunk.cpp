#include "chunk.h"
#include "random"
#include "iostream"

void field::Chunk::generate_room(bool north, bool east, bool south, bool west)  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> roomDist((int)(field::CHUNK_SIZE / 2), field::CHUNK_SIZE - 2);

    int selected_width = roomDist(gen);
    int selected_height = roomDist(gen);

    this->room = new Block *[field::CHUNK_SIZE];
    for (int i = 0; i < field::CHUNK_SIZE; i++) {
        this->room[i] = new Block[field::CHUNK_SIZE];
        for (int j = 0; j < field::CHUNK_SIZE; j++) {
            this->room[i][j] = Block(
                    Tile::Wall,
                    Point(i, j),
                    Point(i + 1, j + 1)
                    );
        }
    }

    unsigned int min_height = (field::CHUNK_SIZE - selected_height) / 2;
    unsigned int min_width = (field::CHUNK_SIZE - selected_width) / 2;

    this->left_bottom = Point(min_width - 1, min_height - 1);
    this->right_top = Point(min_width + selected_width, min_height + selected_height);

    std::uniform_int_distribution<int> randomizer(0, 100);
    for (unsigned int y = min_height; y < min_height + selected_height; y++) {
        for (unsigned int x = min_width; x < min_width + selected_width; x++) {
            if (randomizer(gen) >= 96)
                this->room[y][x].set_block_type(Tile::Small_Wall);
            else if (randomizer(gen) > 96)
                this->room[y][x].set_block_type(Tile::Void);
            else
                this->room[y][x].set_block_type(Tile::Floor);
        }
    }

    if (north)
        for (int i = 0; i <= (field::CHUNK_SIZE / 2); i++)
            this->room[i][field::CHUNK_SIZE / 2].set_block_type(Tile::Floor);
    if (east)
        for (int i = (field::CHUNK_SIZE / 2); i < field::CHUNK_SIZE; i++)
            this->room[field::CHUNK_SIZE / 2][i].set_block_type(Tile::Floor);
    if (south)
        for (int i = (field::CHUNK_SIZE / 2); i < field::CHUNK_SIZE; i++)
            this->room[i][field::CHUNK_SIZE / 2].set_block_type(Tile::Floor);
    if (west)
        for (int i = 0; i <= (field::CHUNK_SIZE / 2); i++)
            this->room[field::CHUNK_SIZE / 2][i].set_block_type(Tile::Floor);
}

void field::Chunk::print_chunk() const {
    for (int i = 0; i < field::CHUNK_SIZE; ++i) {
        for (int j = 0; j < field::CHUNK_SIZE; ++j) {
            room[i][j].print_block();
        }
        std::cout << std::endl;
    }
}

field::Chunk::Chunk(const Chunk &other) {
    this->right_top = other.right_top;
    this->left_bottom = other.left_bottom;
    if (other.room == nullptr)
        this->room = nullptr;
    else {
        this->room = new Block *[field::CHUNK_SIZE];
        for (int i = 0; i < field::CHUNK_SIZE; i++) {
            this->room[i] = new Block[field::CHUNK_SIZE];
            for (int j = 0; j < field::CHUNK_SIZE; j++) {
                this->room[i][j] = other.room[i][j];
            }
        }
    }
}

field::Chunk::Chunk(field::Chunk &&other)  noexcept {
    this->right_top = other.right_top;
    this->left_bottom = other.left_bottom;
    if (other.room == nullptr)
        this->room = nullptr;
    else {
        this->room = other.room;
        other.room = nullptr;
    }
}

field::Chunk& field::Chunk::operator=(const Chunk &other) {
    if (this == &other) return *this;
    this->right_top = other.right_top;
    this->left_bottom = other.left_bottom;
    if (other.room == nullptr)
        this->room = nullptr;
    else {
        this->room = new Block *[field::CHUNK_SIZE];
        for (int i = 0; i < field::CHUNK_SIZE; i++) {
            this->room[i] = new Block[field::CHUNK_SIZE];
            for (int j = 0; j < field::CHUNK_SIZE; j++) {
                this->room[i][j] = other.room[i][j];
            }
        }
    }
    return *this;
}

field::Chunk& field::Chunk::operator=(Chunk &&other) noexcept {
    this->right_top = other.right_top;
    this->left_bottom = other.left_bottom;
    if (other.room == nullptr)
        this->room = nullptr;
    else {
        this->room = other.room;
        other.room = nullptr;
    }
    return *this;
}

field::Chunk::~Chunk() {
    if (this->room == nullptr) return;
    for (int i = 0; i < field::CHUNK_SIZE; ++i)
        delete[] this->room[i];
    delete[] this->room;
}