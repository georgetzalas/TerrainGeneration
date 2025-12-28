cmake_minimum_required(VERSION 3.16)
project(TerrainGeneration C CXX)

add_subdirectory(vendors/glfw)
add_subdirectory(vendors/glm)

add_executable(TerrainGeneration
    main.cpp
    src/core/window.cpp
    src/core/input.cpp
    src/world/terrain.cpp
    src/world/camera.cpp
    src/generator/perlin.cpp
    src/gfx/opengl/renderer.cpp
    src/gfx/opengl/types/shader.cpp
    src/gfx/opengl/types/buffer.cpp
    src/utils/util.cpp
    src/ui/ui_manager.cpp
    src/app/app.cpp
    vendors/imgui/imgui.cpp
    vendors/imgui/imgui_demo.cpp
    vendors/imgui/imgui_draw.cpp
    vendors/imgui/backends/imgui_impl_glfw.cpp
    vendors/imgui/backends/imgui_impl_opengl3.cpp
    vendors/imgui/imgui_tables.cpp
    vendors/imgui/imgui_widgets.cpp

    vendors/glad/glad.c
)

target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendors)
target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendors/glad/include)
target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendors/imgui)
target_link_libraries(TerrainGeneration PRIVATE glfw)
target_link_libraries(TerrainGeneration PRIVATE glm::glm)
