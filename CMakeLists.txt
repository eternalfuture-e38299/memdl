cmake_minimum_required(VERSION 3.5)
project(memdl C)

set(CMAKE_C_STANDARD 11)

add_library(libmemdl STATIC memdl.c)

add_executable(test
        test.c
)

target_link_libraries(test
        libmemdl
)
add_library(test_lib SHARED libtest.c)
