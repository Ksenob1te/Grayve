cmake_minimum_required(VERSION 3.26)

add_library(game_lib game.cpp)
add_library(controller controller.cpp)

target_link_libraries(game_lib controller texture_manager)