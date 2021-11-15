cmake_minimum_required(VERSION 3.10)

project(cpu-rasterizer)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)

include_directories(include)

add_subdirectory(src)

add_subdirectory(test)