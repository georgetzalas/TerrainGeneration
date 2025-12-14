cmake_minimum_required(VERSION 3.16)
project(TerrainGeneration C CXX)

add_subdirectory(vendors/glfw)
add_subdirectory(vendors/glm)

add_executable(TerrainGeneration
    main.cpp
    src/core/window.cpp
    src/core/input.cpp
    src/world/terrain.cpp
    src/generator/perlin.cpp
    src/gfx/opengl/renderer.cpp
    src/gfx/opengl/types/shader.cpp
    src/gfx/opengl/types/buffer.cpp
    src/utils/util.cpp
    vendors/glad/glad.c
)

target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendors)
target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendors/glad/include)
target_link_libraries(TerrainGeneration PRIVATE glfw)
target_link_libraries(TerrainGeneration PRIVATE glm::glm)
