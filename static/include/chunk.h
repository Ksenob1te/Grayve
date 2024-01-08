#ifndef GRAYVE_CHUNK_H
#define GRAYVE_CHUNK_H

#include "point.h"
#include "block.h"

namespace field {
    /**
     * @brief The size of the Chunk.
     */
    const unsigned int CHUNK_SIZE = 32;

    /**
     * @class Chunk
     * @brief Represents a Chunk within the game field.
     */
    class Chunk {
    public:
        Block** room; /**< Pointer to a 2D array of Block pointers representing the Chunk room. */
        Point left_bottom; /**< The coordinates of the bottom-left corner of the Chunk. */
        Point right_top; /**< The coordinates of the top-right corner of the Chunk. */

        /**
         * @brief Default constructor for Chunk class.
         */
        Chunk() : room(nullptr), left_bottom(Point()), right_top(Point()) {}

        /**
         * @brief Copy constructor for Chunk class.
         * @param other The Chunk object to be copied.
         */
        Chunk(const Chunk& other);

        /**
         * @brief Move constructor for Chunk class.
         * @param other The Chunk object to be moved.
         */
        Chunk(Chunk&& other) noexcept;

        /**
         * @brief Assignment operator overload for Chunk class (copy assignment).
         * @param other The Chunk object to be assigned.
         * @return Reference to the assigned Chunk object.
         */
        Chunk& operator=(const Chunk& other);

        /**
         * @brief Move assignment operator overload for Chunk class.
         * @param other The Chunk object to be moved.
         * @return Reference to the moved Chunk object.
         */
        Chunk& operator=(Chunk&& other) noexcept;

        /**
         * @brief Destructor for Chunk class.
         */
        ~Chunk();

        /**
         * @brief Generates the room for the Chunk based on neighboring chunks.
         * @param north Flag indicating whether there is a neighboring Chunk to the north.
         * @param east Flag indicating whether there is a neighboring Chunk to the east.
         * @param south Flag indicating whether there is a neighboring Chunk to the south.
         * @param west Flag indicating whether there is a neighboring Chunk to the west.
         */
        void generate_room(bool north = false, bool east = false, bool south = false, bool west = false);

        /**
         * @brief Prints the visual representation of the Chunk.
         */
        void print_chunk() const;

        /**
         * @brief Gets the Block at the specified coordinates within the Chunk.
         * @param x The X coordinate of the Block.
         * @param z The Z coordinate of the Block.
         * @return Reference to the Block at the specified coordinates.
         */
        [[nodiscard]] Block& get_block(double x, double z) const;
    };
} // namespace field

#endif //GRAYVE_CHUNK_H
