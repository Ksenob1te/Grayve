#include "SFML/Graphics.hpp"
#include "map.h"
#include "iostream"

int main() {
//    sf::RenderWindow window(sf::VideoMode(600, 600), "label");
//    window.setFramerateLimit(60);
//
//    sf::Event event;
//
//    while (window.isOpen())
//    {
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed) window.close();
//            if (event.type == sf::Event::KeyPressed)
//            {
//                if (event.key.code == sf::Keyboard::Escape) window.close();
//            }
//        }
//
//        window.clear();
//        window.display();
//    }
    auto *map = new field::Map(19, 7);
    map->generate_dungeon();
    map->print_map();
    map->print_dungeon();
    int x;
    std::cin >> x;
    return 0;
}
