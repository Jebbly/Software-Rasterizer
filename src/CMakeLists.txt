file(GLOB CPU_RASTERIZER_SOURCES
    geometry/model.cpp
    geometry/vertex.cpp
    image/camera.cpp
    image/framebuffer.cpp
    main.cpp
    renderer.cpp
)

add_executable(${PROJECT_NAME} ${CPU_RASTERIZER_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm_static tinyobjloader)