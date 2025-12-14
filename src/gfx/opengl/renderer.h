#pragma once

#include <gfx/opengl/types/shader.h>
#include <gfx/opengl/types/buffer.h>

namespace Gfx
{
namespace OpenGL
{
    class Renderer
    {
    public:
        static Renderer* GetInstance();

        void Init();
        void Destroy();
        void Render(Shader*, Buffer*);

    private:
        Renderer();

        Renderer(Renderer &other) = delete;
        void operator=(const Renderer&) = delete;

    private:
        static Renderer* renderer;
    };
};
};
