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
    glEnable(GL_DEPTH_TEST);
}

void Gfx::OpenGL::Renderer::Destroy()
{ 
    delete renderer;
}

void Gfx::OpenGL::Renderer::SetMode(Mode& mode)
{
    if(mode == Gfx::OpenGL::Mode::FILL)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if(mode == Gfx::OpenGL::Mode::LINE)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

void Gfx::OpenGL::Renderer::Render(Shader* shader, Buffer* buffer)
{
    buffer->Bind();
    shader->Use();

    texture.Bind(0);
    shader->SetInt("tex", 0);

    uint32_t numberOfStrips   = buffer->GetNumberStrips();
    uint32_t verticesPerStrip = buffer->GetVerticesPerStrip();

    for(unsigned int strip = 0; strip < numberOfStrips; strip++)
    {
        glDrawElements(GL_TRIANGLE_STRIP,  
                       verticesPerStrip, 
                       GL_UNSIGNED_INT,    
                       (void*)(sizeof(unsigned int)
                                 * verticesPerStrip
                                 * strip)); 
    }
}

Gfx::OpenGL::Renderer::Renderer()
{
}
