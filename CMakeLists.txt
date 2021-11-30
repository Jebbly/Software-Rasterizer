cmake_minimum_required(VERSION 3.10)

project(cpu-rasterizer)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external)

include_directories(include)

file(GLOB CPU_RASTERIZER_SOURCES
    src/geometry/model.cpp
    src/geometry/vertex.cpp
    src/image/camera.cpp
    src/image/framebuffer.cpp
    src/renderer.cpp
)

add_library(cpu-rasterizer ${CPU_RASTERIZER_SOURCES})
target_link_libraries(cpu-rasterizer PUBLIC glm_static tinyobjloader)

add_subdirectory(src)

add_subdirectory(test)
