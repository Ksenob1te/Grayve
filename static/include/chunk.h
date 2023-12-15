#ifndef GRAYVE_CHUNK_H
#define GRAYVE_CHUNK_H
#include "point.h"
#include "block.h"

namespace field {
    const unsigned int CHUNK_SIZE = 32;

    class Chunk {
    public:
        Block** room;
        Point left_bottom, right_top;

        Chunk(): room(nullptr), left_bottom(Point()), right_top(Point()) {};
        Chunk(const Chunk &other);
        Chunk(Chunk &&other) noexcept ;

        Chunk& operator=(const Chunk &other);
        Chunk& operator=(Chunk &&other) noexcept;
        ~Chunk();
        void generate_room(bool north = false, bool east = false, bool south = false, bool west = false);
        void print_chunk() const;
    };


}

#endif //GRAYVE_CHUNK_H
