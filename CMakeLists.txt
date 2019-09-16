cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 14)

project(planning)

add_executable(planning src/Map.cpp src/Planner.cpp src/Main.cpp)   
