cmake_minimum_required(VERSION 3.22)
project(raylib_game)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCS src/*.cpp)
include_directories(include)

find_library(RAYLIB_LIB raylib)

add_executable(${PROJECT_NAME} ${SRCS}
        include/projectiles.hpp)
target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB})

