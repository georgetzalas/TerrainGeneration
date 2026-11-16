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

    struct RenderSettings
    {
        bool DepthTest = false;
    };

    class Renderer
    {
    public:
        static Renderer* GetInstance();

        void Init() const;
        void Destroy() const;
        void Render(const Shader* const shader, const Buffer* const buffer) const;
        void SetMode(const Mode& mode) const;

        Gfx::OpenGL::Shader* GetShader(const std::string& name) const;

    private:
        Renderer();
        ~Renderer();

        Renderer(Renderer &other) = delete;
        void operator=(const Renderer&) = delete;

    private:
        static Renderer* renderer;
        std::unordered_map<std::string, Gfx::OpenGL::Shader*> shaders;
    };
};
};
