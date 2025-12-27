#include <iostream>
#include <core/window.h>
#include <core/input.h>
#include <world/terrain.h>
#include <gfx/opengl/renderer.h>
#include <ui/ui_manager.h>

int main()
{
    Core::Window::GetInstance()->Init();
    Core::Input::GetInstance()->Init();
    Gfx::OpenGL::Renderer::GetInstance()->Init();
    UI::UIManager::GetInstance()->Init();

    World::Terrain* terrain = new World::Terrain(256, 256);
    terrain->GenerateTerrain();

    while(Core::Window::GetInstance()->IsOpen())
    {
        Core::Window::GetInstance()->Clear();

        Core::Input::GetInstance()->Update();

        terrain->Update();
        terrain->Render();

        UI::UIManager::GetInstance()->Render();

        Core::Window::GetInstance()->ProcessEvents();
        Core::Window::GetInstance()->SwapBuffers();
    }

    delete terrain;

    UI::UIManager::GetInstance()->Destroy();
    Gfx::OpenGL::Renderer::GetInstance()->Destroy();
    Core::Input::GetInstance()->Destroy();
    Core::Window::GetInstance()->Destroy();

    return 0;
}
