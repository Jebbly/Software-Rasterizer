cmake_minimum_required(VERSION 3.10)

project(cpu-rasterizer)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(external)

include_directories(include)

add_subdirectory(src)