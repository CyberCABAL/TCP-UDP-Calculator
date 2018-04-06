cmake_minimum_required(VERSION 2.8)

project(o2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

add_executable(o2 client.cpp)
