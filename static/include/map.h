#ifndef GRAYVE_MAP_H
#define GRAYVE_MAP_H

#include "random"
#include "vector"
#include "chunk.h"
#include "entity.h"
#include <set>

class Entity;

namespace field {
    struct Chunk_Connector {
        Chunk room = Chunk();
        int x = 0;
        bool connected_north = false;
        bool connected_east = false;
        bool connected_south = false;
        bool connected_west = false;
    };

    class Map {
    private:
        std::vector<std::vector<Chunk_Connector>> rooms;
        int map_size;
        int starter_x, starter_y;
    public:
        std::set<Entity*> entity_set;
        Map();
        explicit Map(int map_size);
        ~Map();

        [[nodiscard]] int get_map_size() const {return this->map_size;}
        void generate_room_map(int numRooms);

        [[nodiscard]] int get_starter_x() const {return this->starter_x;};
        [[nodiscard]] int get_starter_y() const {return this->starter_y;};
        [[nodiscard]] const Chunk& get_starter() const;
        [[nodiscard]] const Chunk& get_chunk(int x, int y) const;
        void print_starter() const;
        void print_chunk(int x, int y) const;
        void print_map() const;
        void update();
        void add_entity(Entity *entity);
        void remove_entity(Entity *entity);
    };
}

#endif //GRAYVE_MAP_H
