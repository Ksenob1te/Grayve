
add_library(creeper STATIC creeper.cpp)
set(DYNAMIC_LIBS creeper ${DYNAMIC_LIBS} PARENT_SCOPE)