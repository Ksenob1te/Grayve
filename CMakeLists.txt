cmake_minimum_required(VERSION 3.26)
project(Grayve)

set(CMAKE_CXX_STANDARD 20)
add_executable(${PROJECT_NAME} main.cpp)

#set(SFML_STATIC_LIBRARIES TRUE)
#set(SFML_DIR SFML/lib/cmake/SFML)
#find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
#include_directories(SFML/include)

find_package(GLUT REQUIRED)
if(NOT GLUT_FOUND)
    message(ERROR "GLUT not found!")
endif(NOT GLUT_FOUND)

#find_package(glfw3 3.3 REQUIRED)

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

#target_link_libraries(Grayve sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
include_directories(static/include graphic/include)

add_subdirectory(static)
add_subdirectory(graphic)
add_subdirectory(game)
target_link_libraries(camera entity)
target_link_libraries(game_lib entity camera chunk map draw_map draw_entity thread_pool)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} game_lib draw_map)