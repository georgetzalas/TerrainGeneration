#include <world/terrain_chunk.h>

#include <algorithm>
#include <cfloat>

World::TerrainChunk::TerrainChunk(uint32_t chunkX, uint32_t chunkZ, uint32_t chunkSize,
                                  uint32_t terrainWidth, uint32_t terrainDepth)
{
    this->chunkX       = chunkX;
    this->chunkZ       = chunkZ;
    this->terrainWidth = terrainWidth;
    this->terrainDepth = terrainDepth;

    startX = chunkX * chunkSize;
    startZ = chunkZ * chunkSize;

    // Border chunks can be smaller than chunkSize if the terrain
    // size is not an exact multiple of the chunk size
    // A chunk owns chunkSize QUAD columns/rows, which needs chunkSize+1 VERTICES.
    // The extra edge column is duplicated with the next chunk (same world position,
    // same height) so borders are seamless. Clamp at the terrain edge.
    sizeX = std::min(chunkSize, terrainWidth  - 1 - startX) + 1;
    sizeZ = std::min(chunkSize, terrainDepth - 1 - startZ) + 1;

    buffer = new Gfx::OpenGL::Buffer();
}

World::TerrainChunk::~TerrainChunk()
{
    delete buffer;
}

void World::TerrainChunk::Generate(Generator::PerlinNoise& perlin, float normalizationFactor)
{
    vertices.clear();
    vertices.reserve((size_t)sizeX * (size_t)sizeZ);

    boundsMin = glm::vec3(FLT_MAX,  FLT_MAX,  FLT_MAX);
    boundsMax = glm::vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for(uint32_t z = 0; z < sizeZ; z++)
    {
        for(uint32_t x = 0; x < sizeX; x++)
        {
            uint32_t gx = startX + x;   // global grid coordinates
            uint32_t gz = startZ + z;

            Vertex v;

            v.position.x = gx - terrainWidth / 2.0f;
            v.position.y = perlin.GetHeight(terrainWidth * gz + gx) * normalizationFactor;
            v.position.z = gz - terrainDepth / 2.0f;

            // GLOBAL UVs so the full-terrain splat texture stays continuous
            // across chunk borders
            v.uv.x = gx / (float)(terrainWidth - 1);
            v.uv.y = gz / (float)(terrainDepth - 1);

            boundsMin = glm::min(boundsMin, v.position);
            boundsMax = glm::max(boundsMax, v.position);

            vertices.push_back(v);
        }
    }

    buffer->FillBuffer(sizeof(Vertex) * vertices.size(), vertices, sizeX, sizeZ);
}

void World::TerrainChunk::Render(Gfx::OpenGL::Shader* shader)
{
    if(vertices.size() <= 0) return;

    Gfx::OpenGL::Renderer::GetInstance()->Render(shader, buffer);
}

const glm::vec3& World::TerrainChunk::GetMin() const
{
    return boundsMin;
}

const glm::vec3& World::TerrainChunk::GetMax() const
{
    return boundsMax;
}

glm::vec3 World::TerrainChunk::GetCenter() const
{
    return (boundsMin + boundsMax) * 0.5f;
}

uint32_t World::TerrainChunk::GetStartX() const
{
    return startX;
}

uint32_t World::TerrainChunk::GetStartZ() const
{
    return startZ;
}

uint32_t World::TerrainChunk::GetSizeX() const
{
    return sizeX;
}

uint32_t World::TerrainChunk::GetSizeZ() const
{
    return sizeZ;
}

void World::TerrainChunk::SetChunkID(uint32_t chunkID)
{
    this->chunkID = chunkID;
}

uint32_t World::TerrainChunk::GetChunkID() const
{
    return chunkID;
}

const std::vector<Vertex>& World::TerrainChunk::GetVertices() const
{
    return vertices;
}