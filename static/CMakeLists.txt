cmake_minimum_required(VERSION 3.26)

add_subdirectory(src/field)
add_subdirectory(src/entity)
add_subdirectory(src/thread_pool)
#target_include_directories(game PUBLIC src)
#target_include_directories(game PUBLIC src/entity)
#target_include_directories(game PUBLIC src/field)


target_link_libraries(map thread_pool)