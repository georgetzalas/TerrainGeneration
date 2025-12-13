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

    perlin.SetWidth(width);
    perlin.SetDepth(depth);
    perlin.SetFrequency(32.0f);
    perlin.SetOctaves(8);
    perlin.SetSeed(5324);
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

uint32_t World::Terrain::GetWidth() const
{
    return width;
}

void World::Terrain::SetWidth(uint32_t width)
{
    this->width = width;
}

uint32_t World::Terrain::GetDepth() const
{
    return depth;
}

void World::Terrain::SetDepth(uint32_t depth)
{
    this->depth = depth;
}

void World::Terrain::PrintTerrainValues() const
{
    for(int z=0; z<depth; z++)
    {
        for(int x=0; x<width; x++)
        {
            int index = z + width * x;
            std::cout << "(" << terrain[index].x << ", " << terrain[index].y << ", " << terrain[index].z << "), ";
        }
        std::cout << std::endl;
    }
}
