cmake_minimum_required(VERSION 3.26)

add_library(draw_block draw_block.cpp)
target_link_libraries(draw_block ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
