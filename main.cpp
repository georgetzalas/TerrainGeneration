#include <iostream>
#include <core/window.h>
#include <core/input.h>
#include <world/terrain.h>

int main()
{
    Core::Window::GetInstance()->Init();
    Core::Input::GetInstance()->Init();

    World::Terrain terrain(256, 256);
    terrain.GenerateTerrain();
    //terrain.PrintTerrainValues();

    while(Core::Window::GetInstance()->IsOpen())
    {
        Core::Window::GetInstance()->Clear();

        terrain.RenderTerrain();

        Core::Window::GetInstance()->ProcessEvents();
        Core::Window::GetInstance()->SwapBuffers();
    }

    Core::Window::GetInstance()->Destroy();
    Core::Input::GetInstance()->Destroy();

    return 0;
}
