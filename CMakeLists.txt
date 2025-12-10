cmake_minimum_required(VERSION 3.16)
project(TerrainGeneration CXX)

add_subdirectory(vendors/glfw)

add_executable(TerrainGeneration
    main.cpp
)

target_link_libraries(TerrainGeneration PRIVATE glfw)
