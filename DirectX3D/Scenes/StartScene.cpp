#include "Framework.h"
#include "StartScene.h"

StartScene::StartScene()
{
	backGroundQuad = new Quad(L"Textures/UI/StartSceneQuad.png");
	backGroundQuad->Pos() = { CENTER_X, CENTER_Y };

	startButton = new Button(L"Textures/UI/StartButton.png");
	startButton->SetTag("startB");
	startButton->Load();
	startButton->SetParamEvent(bind(&StartScene::PushStartButton, this));
	//SetParamEvent(bind(&Inventory::GetItem, inventory, placeholders::_1));
}

StartScene::~StartScene()
{
	delete backGroundQuad;

	delete startButton;
}

void StartScene::Update()
{
	backGroundQuad->UpdateWorld();

	startButton->Update();
}

void StartScene::PreRender()
{
}

void StartScene::Render()
{
	
}

void StartScene::PostRender()
{
	backGroundQuad->Render();

	startButton->Render();
}

void StartScene::GUIRender()
{
	backGroundQuad->GUIRender();

	startButton->GUIRender();
}

void StartScene::PushStartButton()
{
	SceneManager::Get()->Remove("Start");
	SceneManager::Get()->Add("Main");
}
