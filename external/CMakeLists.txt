set(BUILD_STATIC_LIBS ON)
add_subdirectory(glm)

add_library(tinyobjloader INTERFACE)
target_include_directories(tinyobjloader INTERFACE tinyobjloader)

add_subdirectory(catch2)