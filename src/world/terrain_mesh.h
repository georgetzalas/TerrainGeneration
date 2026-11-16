#pragma once

#include <cstdint>
#include <vector>
#include <utils/types.h>
#include <gfx/opengl/types/buffer.h>
#include <gfx/opengl/types/shader.h>
#include <gfx/opengl/renderer.h>
#include <generator/perlin.h>

namespace World{
class TerrainMesh
{
public:
    TerrainMesh(uint32_t terrainWidth, uint32_t terrainDepth);
    ~TerrainMesh();

    void Generate(Generator::PerlinNoise& perlin, float normalizationFactor);
    void Render(Gfx::OpenGL::Shader* shader);

    const std::vector<Vertex>& GetVertices() const;

private:
    uint32_t terrainWidth, terrainDepth;
    Gfx::OpenGL::Buffer* buffer;
    std::vector<Vertex>  vertices;
};
};