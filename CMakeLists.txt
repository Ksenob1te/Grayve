cmake_minimum_required(VERSION 3.26)
project(Grayve)

set(CMAKE_CXX_STANDARD 17)

add_executable(Grayve main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(SFML/include)

target_link_libraries(Grayve sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

add_subdirectory(static)
target_link_libraries(Grayve game)