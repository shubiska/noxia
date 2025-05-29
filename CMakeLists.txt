cmake_minimum_required(VERSION 4.0)
project(Noxia C)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")
set(CMAKE_LINKER lld-link)

add_library(Noxia STATIC src/noxia.c)
target_include_directories(Noxia PUBLIC include)

# Examples
add_executable(Window examples/window.c)
target_link_libraries(Window Noxia)

if(WIN32)
    target_link_options(Window PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")
endif()
