cmake_minimum_required(VERSION 3.26)

add_library(static_tests OBJECT
        block_test.cpp
        point_tests.cpp
        chunk_test.cpp
        map_tests.cpp
        collider_test.cpp
)