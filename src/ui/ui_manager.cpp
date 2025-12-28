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
}

void UI::UIManager::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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

        if(ImGui::TreeNode("Terrain Generation Settings"))
        {
            static int width = 256, depth = 256;
            static int seed = 2004, octaves = 8;
            static float frequency = 16.0f;
            static float offset    = 16.0f;

            ImGui::InputInt("Width", &width);
            ImGui::InputInt("Depth", &depth);
            ImGui::InputInt("Seed", &seed);
            ImGui::InputInt("Octaves", &octaves);
            ImGui::InputFloat("Frequency", &frequency);
            ImGui::InputFloat("Y Offset", &offset);

            terrain->SetWidth(width);
            terrain->SetDepth(depth);

            terrain->GetPerlin().SetWidth(width);
            terrain->GetPerlin().SetDepth(depth);
            terrain->GetPerlin().SetSeed(seed);
            terrain->GetPerlin().SetFrequency(frequency);
            terrain->GetPerlin().SetOctaves(octaves);
            terrain->GetPerlin().SetOffset(offset);

            if(ImGui::Button("Generate"))
            {
                terrain->GenerateTerrain();
            }

            ImGui::TreePop();
        }

        if(ImGui::TreeNode("Data"))
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