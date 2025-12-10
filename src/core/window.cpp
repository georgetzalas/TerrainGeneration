#include <core/window.h>

Core::Window* Core::Window::window = nullptr;

void window_resize(GLFWwindow* window, int width, int height)
{
    Core::Window::GetInstance()->SetWidth(width);
    Core::Window::GetInstance()->SetHeight(height);
}


Core::Window* Core::Window::GetInstance()
{
    if(window == nullptr)
        window = new Window(WIDTH, HEIGHT, std::string(TITLE));
    return window;
}

Core::Window::Window(uint32_t width, uint32_t height, const std::string& title)
{
    this->width  = width;
    this->height = height;
    this->title  = title;
}

uint32_t Core::Window::GetHeight()
{
    return this->height;
}

void Core::Window::SetHeight(uint32_t height)
{
    this->height = height;
}

uint32_t Core::Window::GetWidth()
{
    return this->width;
}

void Core::Window::SetWidth(uint32_t width)
{
    this->width = width;
}

GLFWwindow* Core::Window::GetWindow()
{
    return glfwWindow;
}

bool Core::Window::IsOpen()
{
    return !glfwWindowShouldClose(glfwWindow);
}

void Core::Window::Clear()
{
    glViewport(0, 0, Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Core::Window::ProcessEvents()
{
    glfwPollEvents();
}

void Core::Window::SwapBuffers()
{
    glfwSwapBuffers(glfwWindow);
}

void Core::Window::Init()
{
    if(!glfwInit())
    {
        std::cerr << "Could not initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if(!glfwWindow)
    {
        std::cerr << "Could not crete GLFW window" << std::endl;
        return;
    }

    glfwMakeContextCurrent(glfwWindow);
    glfwSetWindowSizeCallback(glfwWindow, window_resize);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

}

void Core::Window::Destroy()
{
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
    delete window;
}
