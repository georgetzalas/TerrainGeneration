#pragma once

#include <gfx/opengl/types/shader.h>
#include <gfx/opengl/types/buffer.h>
#include <gfx/opengl/types/texture.h>

namespace Gfx
{
namespace OpenGL
{
    enum class Mode
    {
        FILL = 0,
        LINE
    };

    class Renderer
    {
    public:
        static Renderer* GetInstance();

        void Init();
        void Destroy();
        void Render(Shader*, Buffer*);
        void SetMode(Mode& mode);

    private:
        Renderer();

        Renderer(Renderer &other) = delete;
        void operator=(const Renderer&) = delete;

    private:
        static Renderer* renderer;
        Gfx::OpenGL::Texture texture = Gfx::OpenGL::Texture("res/textures/rocks.jpg");
    };
};
};
