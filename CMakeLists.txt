cmake_minimum_required(VERSION 3.28)
project(Pong)

set(CMAKE_CXX_STANDARD 20)

find_library(RAYLIB raylib)

add_executable(Pong main.cpp)
target_link_libraries(Pong ${RAYLIB})
