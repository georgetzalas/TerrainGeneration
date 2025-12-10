cmake_minimum_required(VERSION 3.16)
project(TerrainGeneration C CXX)

add_subdirectory(vendors/glfw)

add_executable(TerrainGeneration
    main.cpp
    src/core/window.cpp
    src/core/input.cpp
    vendors/glad/glad.c
)

target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendors/glad/include)
target_link_libraries(TerrainGeneration PRIVATE glfw)
