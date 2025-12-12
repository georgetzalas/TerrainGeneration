#include <world/terrain.h>

World::Terrain::Terrain(uint32_t width, uint32_t depth)
{
    this->width       = width;
    this->depth       = depth;
    this->terrainData = terrainData;
}

World::Terrain::~Terrain()
{
    delete terrainData;
}

void World::Terrain::GenerateTerrain()
{
    //terrainData = 
    //Generator::CreateTerrain(GENERATOR_TYPE::PERLIN);
}

void World::Terrain::RenderTerrain()
{
    //GFX::OpenGL::Render(terrainData);
}
