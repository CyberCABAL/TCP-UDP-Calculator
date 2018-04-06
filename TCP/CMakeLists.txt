cmake_minimum_required(VERSION 2.8)

project(o2)


find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

add_executable(o2 server.cpp)
target_link_libraries(o2 pthread)
