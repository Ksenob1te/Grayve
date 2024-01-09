cmake_minimum_required(VERSION 3.26)
project(Grayve)

set(CMAKE_CXX_STANDARD 20)
add_executable(${PROJECT_NAME} main.cpp)

find_package(GLUT REQUIRED)
if(NOT GLUT_FOUND)
    message(ERROR "GLUT not found!")
endif(NOT GLUT_FOUND)


find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)


link_directories(${path_to_SOIL})

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
include_directories(static/include graphic/include)
include_directories(dynamiclib)
include_directories(testlib)
#include_directories(dynamiclink)

add_executable(TEST testlib/catch.hpp test.cpp)
set_target_properties(TEST PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(static)
add_subdirectory(graphic)
add_subdirectory(game)
add_subdirectory(dynamiclib)
#add_subdirectory(dynamiclink)

#add_library(plugin INTERFACE static/include/enemy.h)
#target_link_libraries(plugin_manager plugin)
#target_link_libraries(library_manager plugin)

message(${DYNAMIC_LIBS})

target_link_libraries(camera entity)
target_link_libraries(draw_entity texture_manager)
target_link_libraries(map enemy creeper)
target_link_libraries(game_lib entity camera chunk map draw_map draw_entity)

foreach (loopVAR IN LISTS ${DYNAMIC_LIBS})
    target_link_libraries(loopVAR enemy)
    target_link_libraries(game_lib loopVAR )
endforeach()

set(MY_INCLUDE_LIBS soil ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} game_lib draw_map ${DYNAMIC_LIBS} )

target_link_libraries(${PROJECT_NAME} ${MY_INCLUDE_LIBS})
target_link_libraries(TEST static_tests ${MY_INCLUDE_LIBS} )
add_compile_options(--coverage)
add_link_options(--coverage)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
