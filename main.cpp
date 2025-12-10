#include <iostream>
#include <core/window.h>
#include <core/input.h>

int main()
{
    std::cout << "Hello Terrain" << std::endl;
    Core::Window::GetInstance()->Init();
    Core::Input::GetInstance()->Init();

    while(Core::Window::GetInstance()->IsOpen())
    {
        uint32_t width  = Core::Window::GetInstance()->GetWidth();
        uint32_t height = Core::Window::GetInstance()->GetHeight();
        //std::cout << width << " " << height << std::endl;

        Core::Input::GetInstance()->Update();

        if(Core::Input::GetInstance()->IsKeyboardKeyDown(GLFW_KEY_A))
        {
            std::cout << "A" << std::endl;
        }

        if(Core::Input::GetInstance()->IsKeyboardKeyPressed(GLFW_KEY_B))
        {
            std::cout << "B" << std::endl;
        }

        Core::Window::GetInstance()->Clear();
        Core::Window::GetInstance()->ProcessEvents();
        Core::Window::GetInstance()->SwapBuffers();
    }

    Core::Window::GetInstance()->Destroy();
    Core::Input::GetInstance()->Destroy();

    return 0;
}
