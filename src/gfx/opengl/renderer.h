#pragma once

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
        void Render();

    private:
        Renderer();

        Renderer(Renderer &other) = delete;
        void operator=(const Renderer&) = delete;

    private:
        static Renderer* renderer;
    };
};
};
