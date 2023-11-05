cmake_minimum_required(VERSION 3.26)

add_library(game STATIC models/game.cpp models/game.h)
target_include_directories(game PUBLIC models)
target_include_directories(game PUBLIC models/field)
add_subdirectory(models/field)

target_link_libraries(game field)