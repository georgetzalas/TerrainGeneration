#pragma once

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include <utils/types.h>
#include <gfx/opengl/types/buffer.h>
#include <gfx/opengl/types/shader.h>
#include <gfx/opengl/renderer.h>
#include <generator/perlin.h>
#include <core/logger.h>

namespace World
{
    class TerrainChunk
    {
    public:
        // chunkX/chunkZ = position in the chunk grid, chunkSize = vertices per chunk side
        TerrainChunk(uint32_t chunkX, uint32_t chunkZ, uint32_t chunkSize,
                     uint32_t terrainWidth, uint32_t terrainDepth);
        ~TerrainChunk();

        // Builds this chunk's vertices by sampling the GLOBAL heightmap
        void Generate(Generator::PerlinNoise& perlin, float normalizationFactor);

        // Assumes the shader is already in Use and globals (view/projection) are set
        void Render(Gfx::OpenGL::Shader* shader);

        // World-space AABB, used by frustum culling in Phase 2
        const glm::vec3& GetMin() const;
        const glm::vec3& GetMax() const;
        glm::vec3 GetCenter() const;

        uint32_t GetStartX() const;
        uint32_t GetStartZ() const;
        uint32_t GetSizeX() const;
        uint32_t GetSizeZ() const;

        const std::vector<Vertex>& GetVertices() const;

    private:
        uint32_t chunkX, chunkZ;           // grid coordinates
        uint32_t startX, startZ;           // global grid coordinate of the first vertex
        uint32_t sizeX, sizeZ;             // actual vertex size (border chunks may be smaller)
        uint32_t terrainWidth, terrainDepth;

        glm::vec3 boundsMin, boundsMax;

        Gfx::OpenGL::Buffer* buffer;
        std::vector<Vertex>  vertices;
    };
};