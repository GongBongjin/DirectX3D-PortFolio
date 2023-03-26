#include "Framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	terrain = new Terrain();
	terrain->SetTag("Terrain");

	revenant = new Revenant();
	revenant->SetTag("Revenant");
	revenant->Load();
	revenant->GetTerrain(terrain);

	CAM->SetTarget(revenant);
	CAM->TargetOptionLoad("test");
	//CAM->LookAtTarget();

	EnemyManager::Get();
	//EnemyManager::Get()->SetTarget(revenant);

	skybox = new Skybox(L"Textures/Landscape/BlueSky.dds");

}

MainScene::~MainScene()
{
	delete terrain;

	delete revenant;

	EnemyManager::Delete();

	delete skybox;
}

void MainScene::Update()
{
	terrain->UpdateWorld();

	revenant->Update();

	EnemyManager::Get()->Update();
}

void MainScene::PreRender()
{
}

void MainScene::Render()
{
	skybox->Render();

	terrain->Render();

	revenant->Render();

	EnemyManager::Get()->Render();
}

void MainScene::PostRender()
{
	revenant->PostRender();
}

void MainScene::GUIRender()
{
	//terrain->GUIRender();

	revenant->GUIRender();

	EnemyManager::Get()->GUIRender();
}

void MainScene::Start()
{
}

void MainScene::End()
{
}
