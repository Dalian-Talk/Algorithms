cmake_minimum_required(VERSION 3.17)
project(Algorithms)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Leetcode)

add_executable(Algorithms main.cpp Leetcode/LT_0004_median_of_two_sorted_arrays.cpp)