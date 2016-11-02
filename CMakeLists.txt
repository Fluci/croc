cmake_minimum_required(VERSION 2.8.1)
project (Croc) # projet name

set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
set (CMAKE_CXX_FLAGS "-Wall -Wextra ${CMAKE_CXX_FLAGS}")
set (CMAKE_CXX_FLATS "-O3 ${CMAKE_CXX_FLAGS}")

# fetch library
add_subdirectory(src/lib)

# fetch examples
add_subdirectory(src/examples)
