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
    Core::Timer::Start();
    {
        ZoneScopedN("Perlin noise generation");
        perlin.GeneratePerlinNoise();
    }
    Core::Timer::Elapsed(perlinTime);

    Core::Timer::Start();

    if(terrainMode == TerrainMode::CHUNKED)
    {
        ZoneScopedN("Chunked generation/upload");
        GenerateChunkedTerrain();
    }
    else if(terrainMode == TerrainMode::MESH)
    {
        ZoneScopedN("Mesh generation/upload");
        GenerateMeshedTerrain();
    }
    else
    {
        Core::Logger::GetInstance()->Log(LogLevel::WARNING, "Not a valid terrain mode");
    }

    Core::Timer::Elapsed(generationTime);

    camera->SetPosition(glm::vec3(0.0f, depth, -(int)depth));
}

void World::Terrain::Render()
{
    Core::Timer::Start();

    if(terrainMode == TerrainMode::CHUNKED)
    {
        TracyGpuZone("Render chunked terrain");
        RenderChunkedTerrain();
    }
    else if(terrainMode == TerrainMode::MESH)
    {
        TracyGpuZone("Render meshed terrain");
        RenderMeshedTerrain();
    }
    else
    {
        Core::Logger::GetInstance()->Log(LogLevel::WARNING, "Not a valid terrain mode");
    }

    Core::Timer::Elapsed(renderTime);
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
    Gfx::OpenGL::Shader* const shader = Gfx::OpenGL::Renderer::GetInstance()->GetShader("chunkDebug");

    shader->Use();
    shader->SetMatrix44f("view", camera->GetViewMatrix());
    shader->SetMatrix44f("projection", camera->GetProjectionMatrix());
    
    if(frustumCulling)
    {
        frustum.SetCamera(*camera);
    }

    renderedChunks = 0;

    for(TerrainChunk* chunk : chunks)
    {
        if(frustumCulling)
        {
            if(!frustum.IsAABBVisible(chunk->GetMin(), chunk->GetMax())) 
            {
                continue;
            }
        }

        shader->SetInt("chunkID", chunk->GetChunkID());
        chunk->Render(shader);
        
        renderedChunks++;
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

World::TerrainMode World::Terrain::GetTerrainMode() const
{
    return terrainMode;
}

void World::Terrain::SetTerrainMode(const TerrainMode& terrainMode)
{
    this->terrainMode = terrainMode;
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

uint32_t World::Terrain::GetChunkX() const
{
    return chunkX;
}

void World::Terrain::SetChunkX(uint32_t chunkX)
{
    this->chunkX = chunkX;
}

uint32_t World::Terrain::GetChunkZ() const
{
    return chunkZ;
}

void World::Terrain::SetChunkZ(uint32_t chunkZ)
{
    this->chunkZ = chunkZ;
}

bool World::Terrain::GetFrustumCulling() const
{
    return frustumCulling;
}

void World::Terrain::SetFrustumCulling(bool frustumCulling)
{
    this->frustumCulling = frustumCulling;
}

double World::Terrain::GetGenerationTime() const
{
    return generationTime;
}

double World::Terrain::GetRenderTime() const
{
    return renderTime;
}

double World::Terrain::GetPerlinTime() const
{
    return perlinTime;
}

int World::Terrain::GetRenderedChunks() const
{
    return renderedChunks;
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
