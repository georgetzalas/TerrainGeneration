#include <ui/ui_manager.h>

UI::UIManager* UI::UIManager::instance = nullptr;

UI::UIManager* UI::UIManager::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new UIManager();
    }
    return instance;
}

UI::UIManager::UIManager()
{

}

UI::UIManager::~UIManager()
{

}

void UI::UIManager::Init()
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    //Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Core::Window::GetInstance()->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    Core::Logger::GetInstance()->Log(LogLevel::INFO, "Initialized UI System");
}

void UI::UIManager::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    Core::Logger::GetInstance()->Log(LogLevel::INFO, "Destroyed UI System");
}

void UI::UIManager::Render()
{
    BeginFrame();
    CreateUI();
    Draw();
}

void UI::UIManager::CreateUI()
{
    //ImGui::ShowDemoWindow();

    ImGui::Begin("Editor");

        if(ImGui::TreeNode("Terrain Settings"))
        {
            static int width = 256, depth = 256;
            static int seed = 2004, octaves = 8;
            static float frequency = 16.0f;
            static float offset    = 16.0f;
            static int chunkSize   = 32;

            ImGui::InputInt("Width", &width);
            ImGui::InputInt("Depth", &depth);
            ImGui::InputInt("Seed", &seed);
            ImGui::InputInt("Octaves", &octaves);
            ImGui::InputFloat("Frequency", &frequency);
            ImGui::InputFloat("Y Offset", &offset);

            const char* items[] = { "Mesh", "Chunk" };
            static int item_current = 0;
            ImGui::Combo("Terrain Type", &item_current, items, IM_COUNTOF(items));

            if(terrain->GetTerrainMode() == World::TerrainMode::CHUNKED)
            {
                ImGui::InputInt("Chunk size", &chunkSize);
            }

            if(ImGui::Button("Generate"))
            {
                terrain->SetWidth(width);
                terrain->SetDepth(depth);
                terrain->SetChunkSize(chunkSize);

                if(item_current == 0)
                {
                    terrain->SetTerrainMode(World::TerrainMode::MESH);
                }
                else if(item_current == 1)
                {
                    terrain->SetTerrainMode(World::TerrainMode::CHUNKED);
                }

                terrain->GetPerlin().SetWidth(width);
                terrain->GetPerlin().SetDepth(depth);
                terrain->GetPerlin().SetSeed(seed);
                terrain->GetPerlin().SetFrequency(frequency);
                terrain->GetPerlin().SetOctaves(octaves);
                terrain->GetPerlin().SetOffset(offset);

                terrain->GenerateTerrain();
            }

            ImGui::TreePop();
        }

        if(ImGui::TreeNode("Render Settings"))
        {
            static bool frustumCulling = false;
            ImGui::Checkbox("Frustum Culling", &frustumCulling);

            terrain->SetFrustumCulling(frustumCulling);

            ImGui::TreePop();
        }

        if(ImGui::TreeNode("Measurements"))
        {
            if(terrain->GetTerrainMode() == World::TerrainMode::MESH)
            {
                uint32_t numOfVertices = terrain->GetWidth() * terrain->GetDepth();
                uint32_t numOfTriangles = 0;

                if(numOfVertices > 0)
                {
                    numOfTriangles = numOfVertices/3;
                }

                std::string vertices = "Number of vertices: " + std::to_string(numOfVertices);
                std::string triangles = "Number of triangles: " + std::to_string(numOfTriangles);

                ImGui::Text(vertices.c_str());
                ImGui::Text(triangles.c_str());
            }
            else if(terrain->GetTerrainMode() == World::TerrainMode::CHUNKED)
            {
                uint32_t numOfVertices  = terrain->GetWidth() * terrain->GetDepth();
                uint32_t numOfTriangles = 0;
                uint32_t totalChunks    = terrain->GetChunkX() * terrain->GetChunkZ();
                uint32_t chunkSize      = terrain->GetChunkSize();
                int renderedChunks      = terrain->GetRenderedChunks();

                if(numOfVertices > 0)
                {
                    numOfTriangles = numOfVertices/3;
                }

                std::string numOfVerticesText       = "Number of vertices: " + std::to_string(numOfVertices);
                std::string numOfTrianglesText      = "Number of triangles: " + std::to_string(numOfTriangles);
                std::string totalChunksText         = "Number of chunks: " + std::to_string(totalChunks) + ", " + std::to_string(chunkSize) + " size each";
                std::string renderedChunksText      = "Rendered chunks: " + std::to_string(renderedChunks);

                ImGui::Text(numOfVerticesText.c_str());
                ImGui::Text(numOfTrianglesText.c_str());
                ImGui::Text(totalChunksText.c_str());
                ImGui::Text(renderedChunksText.c_str());

            }
            else
            {
                ImGui::Text("Unknown terrain mode");
            }

            double terrainGenerationTime = terrain->GetGenerationTime() / (double)1000;
            double perlinTime            = terrain->GetPerlinTime() / (double)1000;
            ImGui::Text(("Perlin Time: " + std::to_string(perlinTime) + "sec").c_str());
            ImGui::Text(("Terrain Generation Time: " + std::to_string(terrainGenerationTime) + "sec").c_str());
            //ImGui::Text(std::to_string(terrain->GetRenderTime()).c_str());

            ImGui::TreePop();
        }


    ImGui::End();
}

void UI::UIManager::Draw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::UIManager::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UI::UIManager::SetTerrain(World::Terrain* terrain)
{
    this->terrain = terrain;
}