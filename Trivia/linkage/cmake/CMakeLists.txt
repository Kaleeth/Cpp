cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(linking_demo)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

# set (CMAKE_RUNTIME_OUTPUT_DIRECTORY .)