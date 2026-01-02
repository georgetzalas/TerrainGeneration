#include <world/terrain.h>

World::Terrain::Terrain(uint32_t width, uint32_t depth)
{
    this->width       = width;
    this->depth       = depth;

    shader            = new Gfx::OpenGL::Shader("res/shaders/basic.vs", "res/shaders/basic.fs");
    buffer            = new Gfx::OpenGL::Buffer();
    camera            = new Camera(glm::vec3(0.0f, 3.0f, -3.0f));

    renderMode        = Gfx::OpenGL::Mode::FILL;
}

World::Terrain::Terrain()
{
    this->width       = 0;
    this->depth       = 0;

    shader            = new Gfx::OpenGL::Shader("res/shaders/basic.vs", "res/shaders/basic.fs");
    buffer            = new Gfx::OpenGL::Buffer();
    camera            = new Camera(glm::vec3(0.0f, 3.0f, -3.0f));

    renderMode        = Gfx::OpenGL::Mode::FILL;
}

World::Terrain::~Terrain()
{
    delete shader;
    delete buffer;
    delete camera;
}

void World::Terrain::GenerateTerrain()
{
    terrain.clear();

    perlin.GeneratePerlinNoise();

    for(int z=0; z<depth; z++)
    {
        for(int x=0; x<width; x++)
        {
            Vertex v;

            v.position.x = x;
            v.position.y = perlin.GetHeight(x, z) * perlin.GetOffset();
            v.position.z = z;

            v.uv.x = x / (float)(width - 1);
            v.uv.y = z / (float)(depth - 1);

            terrain.push_back(v);
        } 
    }

    //TEMPORARY 
    static int ttt = 1;

    if(ttt == 1)
    {
        Gfx::OpenGL::Texture* grass = new Gfx::OpenGL::Texture("res/textures/grass.png");
        Gfx::OpenGL::Texture* dirt  = new Gfx::OpenGL::Texture("res/textures/dirt.png");
        Gfx::OpenGL::Texture* snow  = new Gfx::OpenGL::Texture("res/textures/snow.png");

        TileManager tm;
        tm.LoadTile(grass, Slot::ZERO);
        tm.LoadTile(dirt,  Slot::ONE);
        tm.LoadTile(snow,  Slot::TWO);
        texture = tm.TextureGeneration(width, depth, this);
    
        ttt = 0;
    }
    //-----------//

    buffer->FillBuffer(sizeof(Vertex) * terrain.size(), terrain, width, depth);
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

void World::Terrain::Render()
{
    ZoneScopedN("Terrain Render");
    if(terrain.size() <= 0) return;
    shader->Use();
    shader->SetMatrix44f("view", camera->GetViewMatrix());
    shader->SetMatrix44f("projection", camera->GetProjectionMatrix());
    shader->SetFloat("normalizationFactor", perlin.GetOffset());
    texture->Bind(0);
    shader->SetInt("tex", 0);
    Gfx::OpenGL::Renderer::GetInstance()->SetMode(renderMode);
    Gfx::OpenGL::Renderer::GetInstance()->Render(shader, buffer);
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
            std::cout << "(" << terrain[index].position.x << ", " << terrain[index].position.y << ", " << terrain[index].position.z << "), ";
        }
        std::cout << std::endl;
    }
}

Generator::PerlinNoise& World::Terrain::GetPerlin() 
{
    return perlin;
}

float World::Terrain::GetHeight(uint32_t x, uint32_t z) const
{
    return terrain[width * z + x].position.y;
}

float World::Terrain::GetHeightInterpolated(uint32_t x, uint32_t z) const
{
    float BaseHeight = GetHeight((int)x, (int)z);

    if(((int)x + 1 >= width) || ((int)z + 1 >= depth))
    {
        return BaseHeight;
    }

    float NextXHeight = GetHeight((int)x + 1, (int)z);

    float RatioX = x - floorf(x);

    float InterpolatedHeightX = (float)(NextXHeight - BaseHeight) * RatioX + (float)BaseHeight;

    float NextZHeight = GetHeight((int)x, (int)z + 1);

    float RatioZ = z - floorf(z);

    float InterpolatedHeightZ = (float)(NextZHeight - BaseHeight) * RatioZ + (float)BaseHeight;

    float FinalHeight = (InterpolatedHeightX + InterpolatedHeightZ) / 2.0f;

    return FinalHeight;
}