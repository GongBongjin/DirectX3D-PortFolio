#include "Framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	terrain = new Terrain();
	terrain->SetTag("Terrain");

	aStar = new AStar(20,20);
	aStar->SetNode(terrain);

	BuildingManager::Get();
	aStar->SetNode(BuildingManager::Get()->GetColliders());

	revenant = new Revenant();
	revenant->SetTag("Revenant");
	revenant->Load();
	revenant->SetPlayerAim();
	revenant->GetTerrain(terrain);
	CAM->SetTarget(revenant);
	CAM->TargetOptionLoad("test9");	

	BulletManager::Get();
	EnemyManager::Get();
	EnemyManager::Get()->SetTarget(revenant);
	EnemyManager::Get()->GetTerrain(terrain);
	EnemyManager::Get()->GetAStar(aStar);

	revenant->GetBuildingCollider(BuildingManager::Get()->GetColliders());

	skybox = new Skybox(L"Textures/Landscape/BlueSky.dds");

	ParticleManager::Get()->Add("CommonHit", "TextData/Particles/CommonHit.fx", 30);
	ParticleManager::Get()->Add("Reload", "TextData/Particles/Reload.fx", 30);
}

MainScene::~MainScene()
{
	delete terrain;

	delete aStar;

	BuildingManager::Delete();

	delete revenant;

	BulletManager::Delete();

	EnemyManager::Delete();

	ParticleManager::Delete();

	delete skybox;
}

void MainScene::Update()
{
	terrain->UpdateWorld();

	aStar->Update();

	BuildingManager::Get()->Update();

	revenant->Update();

	BulletManager::Get()->Update();

	EnemyManager::Get()->Update();

	ParticleManager::Get()->Update();
}

void MainScene::PreRender()
{
}

void MainScene::Render()
{
	skybox->Render();
	
	terrain->Render();

	aStar->Render();

	BuildingManager::Get()->Render();

	revenant->Render();
	
	BulletManager::Get()->Render();
	
	EnemyManager::Get()->Render();

	ParticleManager::Get()->Render();
}

void MainScene::PostRender()
{
	revenant->PostRender();

	EnemyManager::Get()->PostRender();
}

void MainScene::GUIRender()
{
	//terrain->GUIRender();

	//BuildingManager::Get()->GUIRender();

	revenant->GUIRender();

	//BulletManager::Get()->GUIRender();

	//EnemyManager::Get()->GUIRender();
}

void MainScene::Start()
{
}

void MainScene::End()
{
}
