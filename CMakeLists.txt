cmake_minimum_required(VERSION 3.25.1)

project(Trading)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(Trading main.cpp)
target_link_libraries(Trading ${SDL2_LIBRARIES})
