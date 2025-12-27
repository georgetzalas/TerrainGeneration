#include <world/terrain.h>

World::Terrain::Terrain(uint32_t width, uint32_t depth)
{
    this->width       = width;
    this->depth       = depth;

    shader            = new Gfx::OpenGL::Shader("res/shaders/basic.vs", "res/shaders/basic.fs");
    buffer            = new Gfx::OpenGL::Buffer();
    camera            = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

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

    perlin.SetWidth(width);
    perlin.SetDepth(depth);
    perlin.SetFrequency(32.0f);
    perlin.SetOctaves(5);
    perlin.SetSeed(2004);
    perlin.SetOffset(16.0f);
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
    projection = camera->GetProjectionMatrix();
    view       = camera->GetViewMatrix();


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

    camera->ProcessMouse(Core::Input::GetInstance()->GetMouseOffsetX(), Core::Input::GetInstance()->GetMouseOffsetY());
}

void World::Terrain::Render()
{
    shader->Use();
    shader->SetMatrix44f("view", view);
    shader->SetMatrix44f("projection", projection);
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
