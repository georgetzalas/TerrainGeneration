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

    /*perlin.SetWidth(width);
    perlin.SetDepth(depth);
    perlin.SetFrequency(8.0f);
    perlin.SetOctaves(8);
    perlin.SetSeed(2004);
    perlin.SetOffset(16.0f);*/
    perlin.GeneratePerlinNoise();

    for(int z=0; z<depth; z++)
    {
        for(int x=0; x<width; x++)
        {
            Vertex v;

            v.x = x;
            v.y = perlin.GetHeight(x, z) * perlin.GetOffset();
            v.z = z;

            terrain.push_back(v);
        } 
    }

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
    if(terrain.size() <= 0) return;
    shader->Use();
    shader->SetMatrix44f("view", camera->GetViewMatrix());
    shader->SetMatrix44f("projection", camera->GetProjectionMatrix());
    shader->SetFloat("normalizationFactor", perlin.GetOffset());
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
            std::cout << "(" << terrain[index].x << ", " << terrain[index].y << ", " << terrain[index].z << "), ";
        }
        std::cout << std::endl;
    }
}

Generator::PerlinNoise& World::Terrain::GetPerlin() 
{
    return perlin;
}