#ifndef GRAYVE_MAP_H
#define GRAYVE_MAP_H

#include "random"
#include "vector.h"
#include "chunk.h"
#include "entity.h"

class Entity; // Forward declaration

namespace field {
    struct Chunk_Connector {
        Chunk room = Chunk();
        int x = 0;
        int y = 0;
        bool connected_north = false;
        bool connected_east = false;
        bool connected_south = false;
        bool connected_west = false;
    };

    /**
     * @class Map
     * @brief Represents the game map consisting of interconnected chunks.
     */
    class Map {
    private:
        tmp::Vector<tmp::Vector<Chunk_Connector>> rooms; /**< 2D vector storing Chunk connectors. */
        int map_size; /**< Size of the map. */
        int starter_x, starter_y; /**< Coordinates for the starting chunk. */

    public:
        std::vector<Entity*> entity_set; /**< Vector storing entities on the map. */
        std::vector<Entity*> new_entity; /**< Vector storing newly added entities. */

        /**
         * @brief Default constructor for Map class.
         */
        Map();

        /**
         * @brief Parameterized constructor for Map class.
         * @param map_size The size of the map.
         */
        explicit Map(int map_size);

        /**
         * @brief Destructor for Map class.
         */
        ~Map();

        // Getter methods

        /**
         * @brief Gets the size of the map.
         * @return The size of the map.
         */
        [[nodiscard]] int get_map_size() const { return this->map_size; }

        /**
         * @brief Gets the X-coordinate of the starting chunk.
         * @return The X-coordinate of the starting chunk.
         */
        [[nodiscard]] int get_starter_x() const { return this->starter_x; }

        /**
         * @brief Gets the Y-coordinate of the starting chunk.
         * @return The Y-coordinate of the starting chunk.
         */
        [[nodiscard]] int get_starter_y() const { return this->starter_y; }

        /**
         * @brief Gets the starting chunk.
         * @return Reference to the starting chunk.
         */
        [[nodiscard]] const Chunk& get_starter() const;

        /**
         * @brief Gets the chunk at the specified coordinates.
         * @param x X-coordinate of the chunk.
         * @param y Y-coordinate of the chunk.
         * @return Reference to the chunk at the specified coordinates.
         */
        [[nodiscard]] const Chunk& get_chunk(int x, int y) const;

        // Other methods...

        /**
         * @brief Generates the room map with a specified number of rooms.
         * @param numRooms The number of rooms to generate.
         */
        void generate_room_map(int numRooms);

        void generate_all_enemies(Entity* player);

        /**
         * @brief Prints the starting chunk.
         */
        void print_starter() const;

        /**
         * @brief Prints the chunk at the specified coordinates.
         * @param x X-coordinate of the chunk.
         * @param y Y-coordinate of the chunk.
         */
        void print_chunk(int x, int y) const;

        /**
         * @brief Prints the entire map.
         */
        void print_map() const;

        /**
         * @brief Updates the map state.
         */
        void update(int chunk_x, int chunk_y);

        /**
         * @brief Adds an entity to the map.
         * @param entity Pointer to the entity to be added.
         */
        void add_entity(Entity* entity);

        /**
         * @brief Removes an entity from the map.
         * @param entity Pointer to the entity to be removed.
         */
        void remove_entity(Entity* entity);

        [[nodiscard]] const Entity& get_player() const;
    };
}

#endif //GRAYVE_MAP_H
