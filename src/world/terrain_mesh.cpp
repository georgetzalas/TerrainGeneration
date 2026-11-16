#include <world/terrain_mesh.h>

World::TerrainMesh::TerrainMesh(uint32_t terrainWidth, uint32_t terrainDepth)
{
    this->terrainWidth = terrainWidth;
    this->terrainDepth = terrainDepth;

    buffer = new Gfx::OpenGL::Buffer();
}

World::TerrainMesh::~TerrainMesh()
{
    delete buffer;
}

void World::TerrainMesh::Generate(Generator::PerlinNoise& perlin, float normalizationFactor)
{
    vertices.clear();

    for(int z=0; z<terrainDepth; z++)
    {
        for(int x=0; x<terrainWidth; x++)
        {
            Vertex v;
        
            v.position.x = x - terrainWidth/2.0f;
            v.position.y = perlin.GetHeight(x, z) * normalizationFactor;
            v.position.z = z - terrainDepth/2.0f;

            v.uv.x = x / (float)(terrainWidth - 1);
            v.uv.y = z / (float)(terrainDepth - 1);

            vertices.push_back(v);
        } 
    }

    buffer->FillBuffer(sizeof(Vertex) * vertices.size(), vertices, terrainWidth, terrainDepth);
}

void World::TerrainMesh::Render(Gfx::OpenGL::Shader* shader)
{
    if(vertices.size() <= 0) return;

    Gfx::OpenGL::Renderer::GetInstance()->Render(shader, buffer);
}

const std::vector<Vertex>& World::TerrainMesh::GetVertices() const
{
    return vertices;
}