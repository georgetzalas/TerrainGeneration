#pragma once

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <core/window.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <world/terrain.h>
#include <string>
#include <core/logger.h>

namespace UI
{
class UIManager
{
public:
    static UIManager* GetInstance();

    void Init();
    void Render();
    void Destroy();

    void SetTerrain(World::Terrain*);

private:
    UIManager();
    ~UIManager();
    void BeginFrame();
    void CreateUI();
    void Draw();

private:
    static UIManager* instance;
    World::Terrain* terrain;
};
};