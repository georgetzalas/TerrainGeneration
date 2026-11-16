#include <world/terrain.h>

World::Terrain::Terrain(uint32_t width, uint32_t depth)
{
    this->width       = width;
    this->depth       = depth;
    camera            = new Camera();
    renderMode        = Gfx::OpenGL::Mode::FILL;
    terrainMode       = TerrainMode::MESH;
}

World::Terrain::Terrain()
{
    this->width       = 0;
    this->depth       = 0;
    camera            = new Camera();
    renderMode        = Gfx::OpenGL::Mode::FILL;
    terrainMode       = TerrainMode::MESH;
}

World::Terrain::~Terrain()
{
    delete camera;
    DeleteChunkedTerrain();
    DeleteMeshedTerrain();
}

void World::Terrain::GenerateTerrain()
{
    perlin.GeneratePerlinNoise();
    if(terrainMode == TerrainMode::CHUNKED)
    {
        GenerateChunkedTerrain();
    }
    else if(terrainMode == TerrainMode::MESH)
    {
        GenerateMeshedTerrain();
    }
    else
    {
        Core::Logger::GetInstance()->Log(LogLevel::WARNING, "Not a valid terrain mode");
    }

    camera->SetPosition(glm::vec3(0.0f, depth, -(int)depth));
}

void World::Terrain::Render()
{
    if(terrainMode == TerrainMode::CHUNKED)
    {
        RenderChunkedTerrain();
    }
    else if(terrainMode == TerrainMode::MESH)
    {
        RenderMeshedTerrain();
    }
    else
    {
        Core::Logger::GetInstance()->Log(LogLevel::WARNING, "Not a valid terrain mode");
    }

}

void World::Terrain::GenerateChunkedTerrain()
{
    DeleteChunkedTerrain();

    chunkX = (width + chunkSize - 1) / chunkSize;
    chunkZ = (depth + chunkSize - 1) / chunkSize;

    for(uint32_t cz = 0; cz < chunkZ; cz++)
    {
        for(uint32_t cx = 0; cx < chunkX; cx++)
        {
            TerrainChunk* chunk = new TerrainChunk(cx, cz, chunkSize, width, depth);
            chunk->SetChunkID(cz+cx);
            chunk->Generate(perlin, perlin.GetOffset());
            chunks.push_back(chunk);
        }
    }

    Core::Logger::GetInstance()->Log(LogLevel::INFO, "Generated chunked terrain");
}

void World::Terrain::DeleteChunkedTerrain()
{
    for(TerrainChunk* chunk : chunks)
    {
        delete chunk;
    }

    chunks.clear();
    chunkX = 0;
    chunkZ = 0;
}

void World::Terrain::RenderChunkedTerrain()
{
    Gfx::OpenGL::Shader* shader = Gfx::OpenGL::Renderer::GetInstance()->GetShader("chunkDebug");

    shader->Use();
    shader->SetMatrix44f("view", camera->GetViewMatrix());
    shader->SetMatrix44f("projection", camera->GetProjectionMatrix());

    for(TerrainChunk* chunk : chunks)
    {
        shader->SetInt("chunkID", chunk->GetChunkID());
        chunk->Render(shader);
    }
}

void World::Terrain::GenerateMeshedTerrain()
{
    DeleteMeshedTerrain();
    terrainMesh = new TerrainMesh(width, depth);
    terrainMesh->Generate(perlin, perlin.GetOffset());
    Core::Logger::GetInstance()->Log(LogLevel::INFO, "Generated meshed terrain");
}

void World::Terrain::DeleteMeshedTerrain()
{
    delete terrainMesh;
}

void World::Terrain::RenderMeshedTerrain()
{
    Gfx::OpenGL::Shader* shader = Gfx::OpenGL::Renderer::GetInstance()->GetShader("basic");

    shader->Use();
    shader->SetMatrix44f("view", camera->GetViewMatrix());
    shader->SetMatrix44f("projection", camera->GetProjectionMatrix());
    shader->SetFloat("normalizationFactor", perlin.GetOffset()); 

    if(terrainMesh)
        terrainMesh->Render(shader);
}

void World::Terrain::Update()
{
    if(Core::Input::GetInstance()->IsKeyboardKeyDown(GLFW_KEY_W))
    {
        camera->ProcessKeyboard(Direction::FORWARD);
    }

    if(Core::Input::GetInstance()->IsKeyboardKeyDown(GLFW_KEY_S))
    {
        camera->ProcessKeyboard(Direction::BACK);
    }

    if(Core::Input::GetInstance()->IsKeyboardKeyDown(GLFW_KEY_A))
    {
        camera->ProcessKeyboard(Direction::LEFT);
    }

    if(Core::Input::GetInstance()->IsKeyboardKeyDown(GLFW_KEY_D))
    {
        camera->ProcessKeyboard(Direction::RIGHT);
    }

    if(Core::Input::GetInstance()->IsKeyboardKeyPressed(GLFW_KEY_O))
    {
        renderMode = Gfx::OpenGL::Mode::FILL;
    }

    if(Core::Input::GetInstance()->IsKeyboardKeyPressed(GLFW_KEY_P))
    {
        renderMode = Gfx::OpenGL::Mode::LINE;
    }

    if(Core::Input::GetInstance()->IsKeyboardKeyDown(GLFW_KEY_LEFT_CONTROL))
    {
        camera->ProcessMouse(Core::Input::GetInstance()->GetMouseOffsetX(), Core::Input::GetInstance()->GetMouseOffsetY());
    }
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

uint32_t World::Terrain::GetChunkSize() const
{
    return chunkSize;
}

void World::Terrain::SetChunkSize(uint32_t chunkSize)
{
    if(chunkSize < 2)
    {
        Core::Logger::GetInstance()->Log(LogLevel::WARNING, "Chunk size must be at least 2 vertices");
        return;
    }

    this->chunkSize = chunkSize;
}

void World::Terrain::PrintTerrainValues() const
{
    /*for(int z=0; z<depth; z++)
    {
        for(int x=0; x<width; x++)
        {
            int index = z + width * x;
            std::cout << "(" << terrain[index].position.x << ", " << terrain[index].position.y << ", " << terrain[index].position.z << "), ";
        }
        std::cout << std::endl;
    }*/
}

Generator::PerlinNoise& World::Terrain::GetPerlin() 
{
    return perlin;
}

float World::Terrain::GetHeight(uint32_t x, uint32_t z) const
{
    /*if(x >= width || z >= depth)
    {
        Core::Logger::GetInstance()->Log(LogLevel::WARNING, "Terrain GetHeight out of bounds");
    }
    return terrain[width * z + x].position.y;*/
}

float World::Terrain::GetRealHeight(uint32_t x, uint32_t z) const
{
    if(x >= width || z >= depth)
    {
        Core::Logger::GetInstance()->Log(LogLevel::WARNING, "Terrain GetRealHeight out of bounds");
    }

    return perlin.GetHeight(width * z + x);
}

float World::Terrain::GetHeightInterpolated(uint32_t x, uint32_t z) const
{
    float BaseHeight = GetRealHeight((int)x, (int)z);

    if(((int)x + 1 >= width) || ((int)z + 1 >= depth))
    {
        return BaseHeight;
    }

    float NextXHeight = GetRealHeight((int)x + 1, (int)z);

    float RatioX = x - floorf(x);

    float InterpolatedHeightX = (float)(NextXHeight - BaseHeight) * RatioX + (float)BaseHeight;

    float NextZHeight = GetRealHeight((int)x, (int)z + 1);

    float RatioZ = z - floorf(z);

    float InterpolatedHeightZ = (float)(NextZHeight - BaseHeight) * RatioZ + (float)BaseHeight;

    float FinalHeight = (InterpolatedHeightX + InterpolatedHeightZ) / 2.0f;

    return FinalHeight;
}