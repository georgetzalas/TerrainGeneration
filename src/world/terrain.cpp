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

    for(int z=0; z<depth; z++)
    {
        for(int x=0; x<width; x++)
        {
            Vertex v;
            v.x = x;
            v.y = 0.0f;
            v.z = z;
            terrain.push_back(v);
        } 
    }
}

void World::Terrain::RenderTerrain()
{
    //GFX::OpenGL::Render(terrainData);
}
