cmake_minimum_required(VERSION 3.26)

add_library(draw_entity STATIC draw_projectile.cpp draw_player.cpp draw_enemy.cpp)
target_link_libraries(draw_entity SOIL ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
