cmake_minimum_required(VERSION 2.8)

project(o4)


find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

add_executable(o4 server.cpp)
target_link_libraries(o4 pthread)
