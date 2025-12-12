#pragma once

#include <cstdint>
#include <vector>
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

    private:
        uint32_t width;
        uint32_t depth;

        std::vector<Vertex> terrain;
    };
};
