cmake_minimum_required(VERSION 4.0)
project(Noxia C)


set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 99)

add_library(Noxia STATIC
    src/noxia.c
)

target_include_directories(Noxia PUBLIC include)

add_executable(Window examples/window.c)
target_link_libraries(Window Noxia)
