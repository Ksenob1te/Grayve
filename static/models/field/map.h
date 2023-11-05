#ifndef GRAYVE_MAP_H
#define GRAYVE_MAP_H

#include "random"
#include "vector"

namespace field {
    enum class Tile {
        Void,
        Floor,
        Wall,
        Small_Wall
    };

    class Map {
    private:
        std::vector<Tile **> rooms;
        int **room_map;
        int room_size;
        int map_size;


    public:
        Map();
        Map(int room_size, int map_size);
        ~Map();
        void generate_room_map(int numRooms);
        void generate_room(bool north = false, bool east = false, bool south = false, bool west = false);
        void print_map();
        void print_room(int index = 0);
        void print_dungeon();

        void generate_dungeon();
    };
}

#endif //GRAYVE_MAP_H
