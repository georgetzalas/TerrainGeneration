cmake_minimum_required(VERSION 3.16)
project(TerrainGeneration C CXX)

file(GLOB_RECURSE SOURCES
    src/main.cpp
    src/*/*.cpp
    src/*/*.c
)

add_library(glad STATIC vendors/glad/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/vendors/glad/include)

add_library(stb STATIC vendors/stb/stb_image.c
                       vendors/stb/stb_image_write.c)
target_include_directories(stb PUBLIC ${CMAKE_SOURCE_DIR}/vendors/stb)

add_library(imgui STATIC vendors/imgui/imgui.cpp
                       vendors/imgui/imgui_demo.cpp
                       vendors/imgui/imgui_draw.cpp
                       vendors/imgui/backends/imgui_impl_glfw.cpp
                       vendors/imgui/backends/imgui_impl_opengl3.cpp
                       vendors/imgui/imgui_tables.cpp
                       vendors/imgui/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC ${CMAKE_SOURCE_DIR}/vendors/imgui)

option(TRACY_ENABLE "" ON)
option(TRACY_ON_DEMAND "" ON)

add_subdirectory(vendors/tracy)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

add_subdirectory(vendors/glfw)

set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(vendors/glm)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(TerrainGeneration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendors/perlin)
target_link_libraries(TerrainGeneration PRIVATE glfw
                                                glm::glm
                                                Tracy::TracyClient
                                                glad
                                                stb
                                                imgui
)
