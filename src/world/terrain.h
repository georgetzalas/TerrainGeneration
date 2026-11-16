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
#include <world/terrain_chunk.h>
#include <world/terrain_mesh.h>
#include <core/window.h>
#include <core/input.h>
#include <core/logger.h>
#include <tile/tile_manager.h>

#include <tracy/Tracy.hpp>

namespace World
{

    enum class TerrainMode
    {
        MESH = 0,
        CHUNKED,
    };

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

        uint32_t GetChunkSize() const;
        void SetChunkSize(uint32_t);

        float GetHeight(uint32_t x, uint32_t z) const;
        float GetRealHeight(uint32_t x, uint32_t z) const;
        float GetHeightInterpolated(uint32_t x, uint32_t z) const;

        void PrintTerrainValues() const;

        Generator::PerlinNoise& GetPerlin();

    private:
        void GenerateChunkedTerrain();
        void DeleteChunkedTerrain();
        void RenderChunkedTerrain();

        void GenerateMeshedTerrain();
        void DeleteMeshedTerrain();
        void RenderMeshedTerrain();

    private:
        //General Terrain info
        uint32_t width;
        uint32_t depth;

        Generator::PerlinNoise perlin;
        Gfx::OpenGL::Mode      renderMode;
        World::Camera*         camera;
        TerrainMode            terrainMode;

        //Mesh based terrain
        World::TerrainMesh* terrainMesh = nullptr;

        //Chunk based terrain
        uint32_t chunkSize = 32;
        uint32_t chunkX;
        uint32_t chunkZ;
        std::vector<TerrainChunk*> chunks;
    };
};
