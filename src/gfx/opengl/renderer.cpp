#include <gfx/opengl/renderer.h>

Gfx::OpenGL::Renderer* Gfx::OpenGL::Renderer::renderer = nullptr; 

Gfx::OpenGL::Renderer* Gfx::OpenGL::Renderer::GetInstance()
{
    if(renderer == nullptr)
        renderer = new Renderer();
    return renderer;
}

void Gfx::OpenGL::Renderer::Init()
{

}

void Gfx::OpenGL::Renderer::Destroy()
{
    delete renderer;
}

void Gfx::OpenGL::Renderer::Render()
{

}

Gfx::OpenGL::Renderer::Renderer()
{

}
