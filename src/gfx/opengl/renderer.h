#pragma once

#include <gfx/opengl/types/shader.h>
#include <gfx/opengl/types/buffer.h>
#include <gfx/opengl/types/texture.h>
#include <core/logger.h>
#include <unordered_map>
#include <string>

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
        Gfx::OpenGL::Shader* GetShader(const std::string& name);

    private:
        Renderer();

        Renderer(Renderer &other) = delete;
        void operator=(const Renderer&) = delete;

    private:
        static Renderer* renderer;
        std::unordered_map<std::string, Gfx::OpenGL::Shader*> shaders;
    };
};
};
