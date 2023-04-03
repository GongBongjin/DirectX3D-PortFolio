#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	terrain = new Terrain();
	aStar = new AStar(40,40);
	aStar->SetNode(terrain);

	BuildingManager::Get();
	aStar->SetNode(BuildingManager::Get()->GetColliders());

	//building = new Building("B0");
	//building->SetTag("B0");
	//building->Load();

}

TestScene::~TestScene()
{
	delete terrain;
	delete aStar;
	BuildingManager::Delete();
	//delete building;
}

void TestScene::Update()
{
	aStar->Update();

	BuildingManager::Get()->Update();
	//building->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	terrain->Render();
	aStar->Render();
	BuildingManager::Get()->Render();
	//building->Render();
}

void TestScene::PostRender()
{
}

void TestScene::GUIRender()
{
	BuildingManager::Get()->GUIRender();
	//building->GUIRender();
}
