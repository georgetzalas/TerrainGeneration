#pragma once

#include <cstdint>
#include <vector>
#include <iostream>
#include <utils/types.h>
#include <generator/perlin.h>
#include <gfx/opengl/types/buffer.h>
#include <gfx/opengl/types/shader.h>
#include <gfx/opengl/renderer.h>
#include <world/camera.h>
#include <core/window.h>
#include <core/input.h>

namespace World
{
    class Terrain
    {
    public:
        Terrain(uint32_t, uint32_t);
        Terrain();
        ~Terrain();

        void GenerateTerrain();
        void Update();
        void Render();

        uint32_t GetWidth() const;
        void SetWidth(uint32_t);

        uint32_t GetDepth() const;
        void SetDepth(uint32_t);

        void PrintTerrainValues() const;

        Generator::PerlinNoise& GetPerlin();

    private:
        uint32_t width;
        uint32_t depth;
        Generator::PerlinNoise perlin;
        Gfx::OpenGL::Buffer* buffer;
        Gfx::OpenGL::Shader* shader;
        Gfx::OpenGL::Mode    renderMode;
        World::Camera*       camera;

        std::vector<Vertex> terrain;
    };
};
