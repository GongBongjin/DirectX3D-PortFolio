#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	revenant = new Revenant();
	revenant->SetTag("Revenant");
	revenant->Load();

	CAM->SetTarget(revenant);
	CAM->TargetOptionLoad("test8");
	CAM->LookAtTarget();
}

TestScene::~TestScene()
{
	delete revenant;

}

void TestScene::Update()
{
	revenant->Update();

}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	revenant->Render();
}

void TestScene::PostRender()
{
	revenant-> PostRender();

}

void TestScene::GUIRender()
{
	revenant->GUIRender();

}
