cmake_minimum_required(VERSION 3.17)
project(Algorithms)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Leetcode)
add_subdirectory(Interview)

add_executable(Algorithms main.cpp)