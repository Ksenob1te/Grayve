#include <ctime>
#include <map.h>
#include "iostream"
#include "random"

field::Map::Map(int map_size) {
    this->map_size = map_size;
    this->rooms = std::vector<std::vector<field::Chunk_Connector>>(map_size);
}

field::Map::Map() {
    this->map_size = 0;
    this->rooms = std::vector<std::vector<field::Chunk_Connector>>(map_size);
}

field::Map::~Map() = default;

void field::Map::generate_room_map(int numRooms) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int room_map[this->map_size][this->map_size];
    for (int y = 0; y < this->map_size; ++y)
        for (int x = 0; x < this->map_size; ++x)
            room_map[y][x] = 0;

    int center = this->map_size / 2;
    if (center >= this->map_size) return;
    int current_x = center, current_y = center;
    this->starter_x = current_x;
    this->starter_y = current_y;

    std::uniform_int_distribution<int> direction(0, 3);
    room_map[center][center] = 1;
    int result_rooms = 1;
    for (int i = 0; i < 50 && result_rooms < numRooms; i++) {
        int current_room = room_map[current_y][current_x];
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
    for (int x = 0; x < this->map_size; ++x) {
        for (int y = 0; y < this->map_size; ++y) {
            if (room_map[y][x] != 0) {
                Chunk_Connector current_connector;
                current_connector.x = x;
                if (y > 0 && abs(room_map[y - 1][x] - room_map[y][x]) == 1 && room_map[y - 1][x] != 0)
                    current_connector.connected_north = true;
                if (x + 1 < this->map_size && abs(room_map[y][x] - room_map[y][x + 1]) == 1 && room_map[y][x + 1] != 0)
                    current_connector.connected_east = true;
                if (y + 1 < this->map_size && abs(room_map[y + 1][x] - room_map[y][x]) == 1 && room_map[y + 1][x] != 0)
                    current_connector.connected_south = true;
                if (x > 0 && abs(room_map[y][x - 1] - room_map[y][x]) == 1 && room_map[y][x - 1] != 0)
                    current_connector.connected_west = true;
                current_connector.room.generate_room(
                        current_connector.connected_north,
                        current_connector.connected_east,
                        current_connector.connected_south,
                        current_connector.connected_west
                );
                this->rooms[y].push_back(current_connector);
            }
        }
    }}

void field::Map::print_chunk(int x, int y) const {
    get_chunk(x, y).print_chunk();
}

void field::Map::print_starter() const {
    this->print_chunk(this->starter_x, this->starter_y);
}

void field::Map::print_map() const {
    std::cout << " ";
    for (int i = 0; i < this->map_size; ++i)
        std::cout << i << " ";
    std::cout << std::endl;
    for (int y = 0; y < this->map_size; ++y) {
        int current_tag = 0;
        std::cout << y;
        for (int x = 0; x < this->map_size; ++x) {
            if (this->rooms[y].size() > current_tag && this->rooms[y][current_tag].x == x) {
                std::cout << "1 ";
                current_tag++;
            } else
                std::cout << "  ";
        }
        std::cout << std::endl;
    }
}

const field::Chunk& field::Map::get_chunk(int x, int y) const {
    for (const auto& room: this->rooms[y])
        if (room.x == x)
            return room.room;
}

const field::Chunk& field::Map::get_starter() const {
    return get_chunk(this->starter_x, this->starter_y);
}

void field::Map::update() {
    for(auto& entity : this->entity_set)
        entity->update();
}

void field::Map::add_entity(Entity *entity) {
    if(entity)
        this->entity_set.insert(entity);
}

void field::Map::remove_entity(Entity *entity) {
    this->entity_set.erase(entity);
}