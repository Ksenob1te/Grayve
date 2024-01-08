cmake_minimum_required(VERSION 3.26)

add_library(texture_manager STATIC texture_manager.cpp)
target_link_libraries(texture_manager ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
