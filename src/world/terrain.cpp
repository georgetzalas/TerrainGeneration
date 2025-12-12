#include <world/terrain.h>

World::Terrain::Terrain(uint32_t width, uint32_t depth)
{
    this->width       = width;
    this->depth       = depth;
}

World::Terrain::~Terrain()
{
}

void World::Terrain::GenerateTerrain()
{
    terrain.clear();
    Generator::PerlinNoise perlin(width, depth, 32.0f, 8, 5342);
    perlin.GeneratePerlinNoise();

    for(int z=0; z<depth; z++)
    {
        for(int x=0; x<width; x++)
        {
            Vertex v;

            v.x = x;
            v.y = perlin.GetHeight(x, z);
            v.z = z;

            terrain.push_back(v);
        } 
    }
}

void World::Terrain::RenderTerrain()
{
    //GFX::OpenGL::Render(terrainData);
}
