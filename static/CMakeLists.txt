cmake_minimum_required(VERSION 3.26)

add_library(game STATIC src/game/game.cpp)
add_subdirectory(src/field)
add_subdirectory(src/entity)

target_include_directories(game PUBLIC src)
target_include_directories(game PUBLIC src/entity)
#target_include_directories(game PUBLIC src/field)


target_link_libraries(game entity chunk map)