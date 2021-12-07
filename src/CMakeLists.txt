add_executable(rasterizer main.cpp)
target_link_libraries(rasterizer PRIVATE cpu-rasterizer)

add_custom_command(
        TARGET rasterizer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/samples/suzanne.obj
                $<TARGET_FILE_DIR:rasterizer>/suzanne.obj)
