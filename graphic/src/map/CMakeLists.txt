cmake_minimum_required(VERSION 3.26)

add_library(draw_map STATIC draw_map.cpp draw_block.h draw_block.cpp)
target_link_libraries(draw_map ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
