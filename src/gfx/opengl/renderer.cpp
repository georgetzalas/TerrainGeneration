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
    Core::Logger::GetInstance()->Log(LogLevel::INFO, "Initialized Render System");
}

void Gfx::OpenGL::Renderer::Destroy()
{ 
    delete renderer;
    Core::Logger::GetInstance()->Log(LogLevel::INFO, "Destroyed Render System");
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
    shaders.insert({"basic", new Shader("./res/shaders/basic.vs", "./res/shaders/basic.fs")});
    shaders.insert({"chunkDebug", new Shader("./res/shaders/chunkDebug.vs", "./res/shaders/chunkDebug.fs")});
}

Gfx::OpenGL::Shader* Gfx::OpenGL::Renderer::GetShader(const std::string& name)
{
    auto it = shaders.find(name);

    if(it != shaders.end())
        return it->second;

    Core::Logger::GetInstance()->Log(LogLevel::WARNING, "Shader with name " + name + " not found");
    return nullptr;
}