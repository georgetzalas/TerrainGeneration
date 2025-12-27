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
    ImGui::ShowDemoWindow();
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