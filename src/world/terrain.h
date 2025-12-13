#pragma once

#include <cstdint>
#include <vector>
#include <iostream>
#include <utils/types.h>
#include <generator/perlin.h>

namespace World
{
    class Terrain
    {
    public:
        Terrain(uint32_t, uint32_t);
        ~Terrain();

        void GenerateTerrain();
        void RenderTerrain();

        uint32_t GetWidth() const;
        void SetWidth(uint32_t);

        uint32_t GetDepth() const;
        void SetDepth(uint32_t);

        void PrintTerrainValues() const;

    private:
        uint32_t width;
        uint32_t depth;
        Generator::PerlinNoise perlin;

        std::vector<Vertex> terrain;
    };
};
