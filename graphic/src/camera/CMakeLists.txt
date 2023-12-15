cmake_minimum_required(VERSION 3.26)

add_library(camera STATIC camera.cpp)
target_link_libraries(camera ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
