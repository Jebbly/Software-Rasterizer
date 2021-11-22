cmake_minimum_required(VERSION 3.10)

project(cpu-rasterizer)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external)

include_directories(include)

file(GLOB CPU_RASTERIZER_SOURCES
    src/geometry/model.cpp
    src/geometry/vertex.cpp
    src/image/camera.cpp
    src/image/framebuffer.cpp
    src/renderer.cpp
)

add_executable(${PROJECT_NAME} src/main.cpp ${CPU_RASTERIZER_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE glm_static tinyobjloader)

add_executable(tests test/tests.cpp ${CPU_RASTERIZER_SOURCES})
target_link_libraries(tests PRIVATE Catch2WithMain glm_static tinyobjloader)
