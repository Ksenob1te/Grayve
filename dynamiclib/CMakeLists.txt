
add_library(creeper STATIC creeper.cpp)
target_link_libraries(creeper ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
set(DYNAMIC_LIBS creeper ${DYNAMIC_LIBS} PARENT_SCOPE)