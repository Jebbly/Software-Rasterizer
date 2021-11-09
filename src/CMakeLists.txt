file(GLOB CPU_RASTERIZER_SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${CPU_RASTERIZER_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm_static tinyobjloader)