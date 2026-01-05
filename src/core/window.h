#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <core/logger.h>

#define WIDTH  1280
#define HEIGHT 800
#define TITLE  "Terrain Generation"

namespace Core 
{
    class Window
    {
    public:
        static Window* GetInstance();

        uint32_t GetHeight();
        void SetHeight(uint32_t height);

        uint32_t GetWidth();
        void SetWidth(uint32_t width);

        GLFWwindow* GetWindow();

        bool IsOpen();
        void Clear();
        void ProcessEvents();
        void SwapBuffers();

        void Init();
        void Destroy();

    private:
        Window(uint32_t, uint32_t, const std::string&);
        
        Window(Window &other) = delete;
        void operator=(const Window&) = delete;

    private:
        static Window* window;
        GLFWwindow* glfwWindow;
        uint32_t width;
        uint32_t height;
        std::string title;
    };
};
