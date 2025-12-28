#pragma once

#include <core/window.h>
#include <core/input.h>
#include <world/terrain.h>
#include <gfx/opengl/renderer.h>
#include <ui/ui_manager.h>

#define TERRAIN_WIDTH  256
#define TERRAIN_HEIGHT 256

class App
{
public:
    App();
    ~App();

    void Init();
    void Run();
    void Destroy();

private:
    World::Terrain* terrain;
};