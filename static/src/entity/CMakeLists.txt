cmake_minimum_required(VERSION 3.26)

add_library(character STATIC character/character.cpp)
add_library(player STATIC character/player/player.cpp)
add_library(enemy STATIC character/enemy/enemy.cpp)
add_library(projectile STATIC projectile/projectile.cpp)

add_library(entity STATIC entity.cpp colliders/collider.cpp)

target_link_libraries(entity character player projectile enemy)