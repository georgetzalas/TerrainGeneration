#include <world/terrain.h>

World::Terrain::Terrain(uint32_t width, uint32_t depth)
{
    this->width       = width;
    this->depth       = depth;

    shader            = new Gfx::OpenGL::Shader("res/shaders/basic.vs", "res/shaders/basic.fs");
    //buffer            = new Gfx::OpenGL::Buffer();
    camera            = new Camera();

    chunkSize         = 32;
    chunkX            = 0;
    chunkZ            = 0;

    renderMode        = Gfx::OpenGL::Mode::FILL;
}

World::Terrain::Terrain()
{
    this->width       = 0;
    this->depth       = 0;

    shader            = new Gfx::OpenGL::Shader("res/shaders/basic.vs", "res/shaders/basic.fs");
    //buffer            = new Gfx::OpenGL::Buffer();
    camera            = new Camera();

    chunkSize         = 32;
    chunkX            = 0;
    chunkZ            = 0;

    renderMode        = Gfx::OpenGL::Mode::FILL;
}

World::Terrain::~Terrain()
{
    DeleteChunks();
    delete shader;
    //delete buffer;
    delete camera;
}

void World::Terrain::GenerateTerrain()
{
    /*terrain.clear();

    perlin.GeneratePerlinNoise();

    for(int z=0; z<depth; z++)
    {
        for(int x=0; x<width; x++)
        {
            Vertex v;
        
            v.position.x = x - width/2.0f;
            v.position.y = perlin.GetHeight(x, z) * perlin.GetOffset();
            v.position.z = z - depth/2.0f;

            v.uv.x = x / (float)(width - 1);
            v.uv.y = z / (float)(depth - 1);

            terrain.push_back(v);
        } 
    }

    camera->SetPosition(glm::vec3(0.0f, depth, -(int)depth));

    //TEMPORARY 
    static int ttt = 1;

    if(ttt == 1)
    {
        Gfx::OpenGL::Texture* snow = new Gfx::OpenGL::Texture("res/textures/snow.png");
        Gfx::OpenGL::Texture* rocks  = new Gfx::OpenGL::Texture("res/textures/rocks.png");
        Gfx::OpenGL::Texture* sand  = new Gfx::OpenGL::Texture("res/textures/sand.png");
        Gfx::OpenGL::Texture* water  = new Gfx::OpenGL::Texture("res/textures/water.png");

        TileManager tm;
        tm.LoadTile(water, Slot::ZERO);
        tm.LoadTile(sand,  Slot::ONE);
        tm.LoadTile(rocks,  Slot::TWO);
        tm.LoadTile(snow,  Slot::THREE);
        texture = tm.TextureGeneration(width, depth, this);
    
        ttt = 0;
    }
    //-----------//

    buffer->FillBuffer(sizeof(Vertex) * terrain.size(), terrain, width, depth);

    Core::Logger::GetInstance()->Log(LogLevel::INFO, "Created terrain " + std::to_string(width) + " " + std::to_string(depth));*/

    DeleteChunks();

    perlin.GeneratePerlinNoise();

    CreateChunks();

    camera->SetPosition(glm::vec3(0.0f, depth, -(int)depth));

    Core::Logger::GetInstance()->Log(LogLevel::INFO,
        "Created terrain " + std::to_string(width) + " " + std::to_string(depth) +
        " in " + std::to_string(chunkX) + "x" + std::to_string(chunkZ) + " chunks");
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

void World::Terrain::CreateChunks()
{
    chunks.clear();

    chunkX = (width + chunkSize - 1) / chunkSize;
    chunkZ = (depth + chunkSize - 1) / chunkSize;

    for(uint32_t cz = 0; cz < chunkZ; cz++)
    {
        for(uint32_t cx = 0; cx < chunkX; cx++)
        {
            TerrainChunk* chunk = new TerrainChunk(cx, cz, chunkSize, width, depth);
            chunk->Generate(perlin, perlin.GetOffset());
            chunks.push_back(chunk);
        }
    }
}

void World::Terrain::DeleteChunks()
{
    for(TerrainChunk* chunk : chunks)
    {
        delete chunk;
    }

    chunks.clear();
    chunkX = 0;
    chunkZ = 0;
}

void World::Terrain::Render()
{
    ZoneScopedN("Terrain Render");

    //if(terrain.size() <= 0) return;
    if(chunks.size() <= 0) return;

    shader->Use();
    shader->SetMatrix44f("view", camera->GetViewMatrix());
    shader->SetMatrix44f("projection", camera->GetProjectionMatrix());
    shader->SetFloat("normalizationFactor", perlin.GetOffset());

    //texture->Bind(0);
    //shader->SetInt("tex", 0);

    Gfx::OpenGL::Renderer::GetInstance()->SetMode(renderMode);
    
    //Gfx::OpenGL::Renderer::GetInstance()->Render(shader, buffer);
    for(TerrainChunk* chunk : chunks)
    {
        chunk->Render(shader);
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