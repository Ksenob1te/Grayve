#include <ctime>
#include "map.h"
#include "iostream"
#include "random"


field::Map::Map(int room_size, int map_size) {
    this->room_size = room_size;
    this->map_size = map_size;
    this->room_map = new int*[map_size];
    for (int i = 0; i < map_size; i++) {
        this->room_map[i] = new int[map_size];
        for (int j = 0; j < map_size; j++)
            this->room_map[i][j] = 0;
    }
}

field::Map::Map() {
    this->room_size = 0;
    this->map_size = 0;
    this->room_map = nullptr;
}

field::Map::~Map() {
    for (int i = 0; i < map_size; i++) {
        delete[] this->room_map[i];
    }
    delete[] this->room_map;

    for (auto room: this->rooms) {
        for (int i = 0; i < room_size; i++) {
            delete[] room[i];
        }
        delete[] room;
    }
}

void field::Map::generate_room_map(int numRooms) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int center = this->map_size / 2;
    if (center >= this->map_size) return;
    int current_x = center, current_y = center;

    std::uniform_int_distribution<int> direction(0, 3);
    this->room_map[center][center] = 1;
    int result_rooms = 1;
    for (int i = 0; i < 50 && result_rooms < numRooms; i++) {
        int current_room = this->room_map[current_y][current_x];
        switch (direction(gen)) {
            case 0:
                if ((current_x + 1) < this->map_size) current_x++;
                break;
            case 1:
                if ((current_x - 1) > 0) current_x--;
                break;
            case 2:
                if ((current_y + 1) < this->map_size) current_y++;
                break;
            case 3:
                if ((current_y - 1) > 0) current_y--;
                break;
        }
        if (room_map[current_y][current_x] == 0) {
            result_rooms++;
            room_map[current_y][current_x] = current_room + 1;
        }
    }
}

void field::Map::generate_room(bool north, bool east, bool south, bool west)  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> roomDist((int)(this->room_size / 2), this->room_size - 2);

    int selected_width = roomDist(gen);
    int selected_height = roomDist(gen);

    Tile **array = new Tile*[this->room_size];
    for (int i = 0; i < room_size; i++) {
        array[i] = new Tile[this->room_size];
        for (int j = 0; j < room_size; j++) {
            array[i][j] = Tile::Wall;
        }
    }
    int min_height = (this->room_size - selected_height) / 2;
    int min_width = (this->room_size - selected_width) / 2;


    std::uniform_int_distribution<int> randomizer(0, 100);
    for (int y = min_height; y < min_height + selected_height; y++) {
        for (int x = min_width; x < min_width + selected_width; x++) {
            if (randomizer(gen) >= 95)
                array[y][x] = Tile::Small_Wall;
            else if (randomizer(gen) > 90)
                array[y][x] = Tile::Void;
            else
                array[y][x] = Tile::Floor;
        }
    }

    if (north)
        for (int i = 0; i <= (this->room_size / 2); i++)
            array[i][this->room_size / 2] = Tile::Floor;
    if (east)
        for (int i = (this->room_size / 2); i < this->room_size; i++)
            array[this->room_size / 2][i] = Tile::Floor;
    if (south)
        for (int i = (this->room_size / 2); i < this->room_size; i++)
            array[i][this->room_size / 2] = Tile::Floor;
    if (west)
        for (int i = 0; i <= (this->room_size / 2); i++)
            array[this->room_size / 2][i] = Tile::Floor;

    this->rooms.push_back(array);

}

void field::Map::generate_dungeon() {
    this->generate_room_map(10);
    for (int y = 0; y < this->map_size; y++) {
        for (int x = 0; x < this->map_size; x++) {
            if (!this->room_map[y][x]) continue;
            bool north = false, south = false, east = false, west = false;
            if (this->room_map[y][x] == 1) this->room_map[y][x] = 2;
            if (y > 0)
                north = abs(this->room_map[y - 1][x] - this->room_map[y][x]) <= 1;
            if (y < this->map_size - 1)
                south = abs(this->room_map[y + 1][x] - this->room_map[y][x]) <= 1;
            if (x > 0)
                east = abs(this->room_map[y][x - 1] - this->room_map[y][x]) <= 1;
            if (x < this->map_size - 1)
                west = abs(this->room_map[y][x + 1] - this->room_map[y][x]) <= 1;
            generate_room(north, east, south, west);
        }
    }
}

void field::Map::print_map() {
    for (int y = 0; y < this->map_size; y++) {
        for (int x = 0; x < this->map_size; x++) {
            char tileChar;
            std::cout << this->room_map[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void field::Map::print_room(int index) {
    Tile **room = this->rooms[index];
    for (int i = 0; i < room_size; ++i) {
        for (int j = 0; j < room_size; ++j) {
            switch (room[i][j]) {
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
        std::cout << std::endl;
    }
}

void field::Map::print_dungeon() {
    int counter = 0;
    int static_counter = 0;
    for (int y = 0; y < this->map_size; y++) {
        for (int i = 0; i < this->room_size; i++) {
            counter = static_counter;
            for (int x = 0; x < this->map_size; x++) {
                if (this->room_map[y][x]) {
                    for (int j = room_size - 1; j >= 0; --j) {
                        switch (this->rooms[counter][i][j]) {
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
                    counter++;
                } else {
                    for (int j = 0; j < room_size; ++j)
                        std::cout << "# ";
                }
            }
            std::cout << std::endl;
        }
        static_counter = counter;
    }
}