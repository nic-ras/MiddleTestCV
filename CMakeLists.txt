cmake_minimum_required(VERSION 3.10)

project(MiddleTestCV)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(APPEND CMAKE_CXX_FLAGS "-O2 -Wall -Werror")

find_package(OpenCV REQUIRED)

add_subdirectory(src)
