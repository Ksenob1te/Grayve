#include <map.h>
#include "iostream"
#include "random"
#include <algorithm>
#include <thread>
#include "thread_pool.h"
#include <chrono>

#include "enemy.h"
#include "creeper.h"


field::Map::Map(int map_size) {
    this->starter_x = 0;
    this->starter_y = 0;
    this->map_size = map_size;
    this->rooms = tmp::Vector<tmp::Vector<field::Chunk_Connector>>(map_size);
}

field::Map::Map() {
    this->starter_x = 0;
    this->starter_y = 0;
    this->map_size = 0;
    this->rooms = tmp::Vector<tmp::Vector<field::Chunk_Connector>>(map_size);
}

field::Map::~Map() = default;



void field::Map::generate_room_map(int numRooms) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int **room_map = new int* [this->map_size]; 
    for (int i = 0; i < this->map_size; i++)
    {
        room_map[i] = new int [this->map_size];
    }

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
    ThreadPool<Chunk_Connector> tp;
    int map_size = this->map_size;
    auto &rooms = this->rooms;
    for (int x = 0; x < this->map_size; ++x) {
        for (int y = 0; y < this->map_size; ++y) {
            if (room_map[y][x] != 0) {
                tp.QueueJob([&, room_map, map_size, x, y](){
                    Chunk_Connector current_connector;
                    current_connector.x = x;
                    current_connector.y = y;
                    if (y > 0 && abs(room_map[y - 1][x] - room_map[y][x]) == 1 && room_map[y - 1][x] != 0)
                        current_connector.connected_north = true;
                    if (x + 1 < map_size && abs(room_map[y][x] - room_map[y][x + 1]) == 1 && room_map[y][x + 1] != 0)
                        current_connector.connected_east = true;
                    if (y + 1 < map_size && abs(room_map[y + 1][x] - room_map[y][x]) == 1 && room_map[y + 1][x] != 0)
                        current_connector.connected_south = true;
                    if (x > 0 && abs(room_map[y][x - 1] - room_map[y][x]) == 1 && room_map[y][x - 1] != 0)
                        current_connector.connected_west = true;
                    current_connector.room.generate_room(
                            current_connector.connected_north,
                            current_connector.connected_east,
                            current_connector.connected_south,
                            current_connector.connected_west
                    );
                    return current_connector;
                });
            }
        }
    }
    tp.Start();
    while(tp.busy()) std::this_thread::sleep_for(std::chrono::milliseconds(500));
    tp.Stop();
    for (auto &conn : tp.return_values) {
        rooms[conn.y].push_back(conn);
    }
}

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
            if (this->rooms[y].get_size() > current_tag && this->rooms[y][current_tag].x == x) {
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

void field::Map::update(int chunk_x, int chunk_y) {
    for (auto ent = this->entity_set.begin(); ent != this->entity_set.end(); ++ent)
        if (*ent != nullptr && (*ent)->get_chunk_x() == chunk_x && (*ent)->get_chunk_y() == chunk_y)
            (*ent)->update();
    this->entity_set.erase(std::remove_if(this->entity_set.begin(),this->entity_set.end(),
                    [](auto x){ return x == nullptr; }), this->entity_set.end());
    for (auto &ent : this->new_entity)
        this->entity_set.push_back(ent);
    this->new_entity.clear();
}

void field::Map::add_entity(Entity *entity) {
    if(entity)
        this->new_entity.push_back(entity);
}

void field::Map::remove_entity(Entity *entity) {
    for (auto &ent : this->entity_set) {
        if(ent == entity) ent = nullptr;
    }
}

const Entity& field::Map::get_player() const {
    for (auto ent : this->entity_set)
        if (ent != nullptr && ent->get_entity_type() == EntityType::PLAYER)
            return *ent;
}

void field::Map::generate_all_enemies(Entity* player) {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (auto& y: this->rooms) {
        for (auto& current_connector: y) {
            std::uniform_int_distribution<unsigned int> height_random(
                    (unsigned) current_connector.room.left_bottom.getZ() + 1,
                    (unsigned) current_connector.room.right_top.getZ() - 1
            );
            std::uniform_int_distribution<unsigned int> width_random(
                    (unsigned) current_connector.room.left_bottom.getX() + 1,
                    (unsigned) current_connector.room.right_top.getX() - 1
            );
            std::uniform_int_distribution<int> enemyType(0, 1);
            int entity_count = 8;
            for (int k = 0; k < entity_count; k++) {
                unsigned curr_height = height_random(gen);
                unsigned curr_width = width_random(gen);
                if (current_connector.room.room[curr_height][curr_width].get_block_type() == Tile::Floor) {
                    if (enemyType(gen) == 1) {
                        auto *creeper = new Creeper(this, current_connector.x, current_connector.y);
                        creeper->setCoordinates(Point(curr_height + 0.5, curr_width + 0.5));
                        creeper->setSpeed(0.05);
                        creeper->set_follow(player);
                    }
                    else {
                        auto *enemy = new Enemy(this, current_connector.x, current_connector.y);
                        enemy->setCoordinates(Point(curr_height + 0.5, curr_width + 0.5));
                        enemy->setSpeed(0.05);
                        enemy->set_follow(player);
                    }
                }
            }
        }
    }
}