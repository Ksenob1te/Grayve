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


link_directories(${path_to_SOIL})
#target_link_libraries(Grayve sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
include_directories(static/include graphic/include)

include_directories(testlib)
add_executable(TEST testlib/catch.hpp test.cpp)
set_target_properties(TEST PROPERTIES LINKER_LANGUAGE CXX)


add_subdirectory(static)
add_subdirectory(graphic)
add_subdirectory(game)

target_link_libraries(camera entity)
target_link_libraries(draw_entity texture_manager)
target_link_libraries(game_lib entity camera chunk map draw_map draw_entity)

set(MY_INCLUDE_LIBS soil ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} game_lib draw_map)

target_link_libraries(${PROJECT_NAME} ${MY_INCLUDE_LIBS})
target_link_libraries(TEST static_tests ${MY_INCLUDE_LIBS} )
add_compile_options(--coverage)
add_link_options(--coverage)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
