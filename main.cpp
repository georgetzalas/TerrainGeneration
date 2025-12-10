#include <iostream>
#include <core/window.h>

int main()
{
    std::cout << "Hello Terrain" << std::endl;
    Core::Window::GetInstance()->Init();

    while(Core::Window::GetInstance()->IsOpen())
    {
        uint32_t width  = Core::Window::GetInstance()->GetWidth();
        uint32_t height = Core::Window::GetInstance()->GetHeight();
        std::cout << width << " " << height << std::endl;
        Core::Window::GetInstance()->Clear();
        Core::Window::GetInstance()->ProcessEvents();
        Core::Window::GetInstance()->SwapBuffers();
    }

    Core::Window::GetInstance()->Destroy();

    return 0;
}
