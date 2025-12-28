#include <app/app.h>

App::App()
{

}

App::~App()
{
}

void App::Init()
{
    Core::Window::GetInstance()->Init();
    Core::Input::GetInstance()->Init();
    Gfx::OpenGL::Renderer::GetInstance()->Init();
    UI::UIManager::GetInstance()->Init();
}

void App::Run()
{
    terrain = new World::Terrain();
    //terrain->GenerateTerrain();

    UI::UIManager::GetInstance()->SetTerrain(terrain);

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
}

void App::Destroy()
{
    delete terrain;

    UI::UIManager::GetInstance()->Destroy();
    Gfx::OpenGL::Renderer::GetInstance()->Destroy();
    Core::Input::GetInstance()->Destroy();
    Core::Window::GetInstance()->Destroy();
}