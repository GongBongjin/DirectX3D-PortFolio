#include "Framework.h"

#include "Scenes/GridScene.h"
#include "Scenes/TerrainScene.h"
#include "Scenes/TerrainEditorScene.h"

#include "Scenes/ModelExportScene.h"
#include "Scenes/ModelRenderScene.h"
#include "Scenes/ModelAnimationScene.h"
#include "Scenes/ParticleScene.h"
#include "Scenes/ParticleToolScene.h"

#include "Scenes/StartScene.h"
#include "Scenes/MainScene.h"
#include "Scenes/BossScene.h"
#include "Scenes/TestScene.h"

GameManager::GameManager()
{
    Create();

    SceneManager::Get()->Create("Grid", new GridScene());
    //SceneManager::Get()->Create("ModelExport", new ModelExportScene());
    //SceneManager::Get()->Create("Start", new ModelRenderScene());
    //SceneManager::Get()->Create("Start", new ModelAnimationScene());
    SceneManager::Get()->Create("Start", new TerrainEditorScene());
    //SceneManager::Get()->Create("Start", new ParticleScene());
    //SceneManager::Get()->Create("Start", new ParticleToolScene());
    //SceneManager::Get()->Create("Start", new StartScene());
    //SceneManager::Get()->Create("Main", new MainScene());
    //SceneManager::Get()->Create("Start", new TestScene());

    SceneManager::Get()->Add("Grid");
    SceneManager::Get()->Add("Start");
    //SceneManager::Get()->Add("Main");
}

GameManager::~GameManager()
{
    Delete();
}

void GameManager::Update()
{
    Keyboard::Get()->Update();
    Timer::Get()->Update();    

    SceneManager::Get()->Update();

    Environment::Get()->Update();

    Audio::Get()->Update();
}

void GameManager::Render()
{
    SceneManager::Get()->PreRender();
    
    Device::Get()->Clear();
    Font::Get()->GetDC()->BeginDraw();
    
    Environment::Get()->Set();    
    SceneManager::Get()->Render();
    
    Environment::Get()->PostSet();
    SceneManager::Get()->PostRender();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    string fps = "F P S : " + to_string(Timer::Get()->GetFPS());
    //Font::Get()->RenderText(fps, { 120, WIN_HEIGHT - 10 });
    
    static bool isActive = true;

    if (isActive)
    {
        ImGui::Begin("Inspector", &isActive);
        Environment::Get()->GUIRender();
        SceneManager::Get()->GUIRender();
        ImGui::End();
    }    

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    
    Font::Get()->GetDC()->EndDraw();

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();
    Observer::Get();
    Audio::Get();
    
    Font::Get()->AddColor("White", 1, 1, 1);
    //Font::Get()->AddStyle("Default", L"배달의민족 주아");
    Font::Get()->AddStyle("Default", L"Beyond The Mountains");
    //Font::Get()->AddStyle("Default_sizeDown", L"Beyond The Mountains", 10.0f);
    
    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");
    //Font::Get()->SetStyle("Default_sizeDown");

    Texture::Add(L"Textures/Color/White.png");
    
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();    
    Observer::Delete();
    Font::Delete();
    SceneManager::Delete();
    Audio::Delete();
    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    
    ImGui::DestroyContext();
}
