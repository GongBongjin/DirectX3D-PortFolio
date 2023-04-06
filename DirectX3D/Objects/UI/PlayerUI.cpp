#include "Framework.h"

PlayerUI::PlayerUI()
{
	icon[0] = new Quad(L"Textures/UI/Attack.png");
	icon[0]->Pos() = { 902.0f, 65.0f, 0.0f };
	icon[0]->Scale() = { 0.75f, 0.75f, 0.0f };
	icon[0]->SetTag("attackIcon");

	icon[1] = new Quad(L"Textures/UI/Reload.png");
	icon[1]->Pos() = { 987.0f, 65.0f, 0.0f };
	icon[1]->Scale() = { 0.75f, 0.75f, 0.0f };
	icon[1]->SetTag("reloadIcon");
	buttonQuad = new Quad(L"Textures/UI/Revenant_AttackUI.png");
	buttonQuad->Pos() = { 950.0f, 60.0f, 0.0f };
	buttonQuad->Scale() = {1.2f, 1.2f, 0.0f};
	buttonQuad->SetTag("quad");
}

PlayerUI::~PlayerUI()
{
	delete buttonQuad;
	delete icon[0];
	delete icon[1];
}


void PlayerUI::Update()
{
	buttonQuad->UpdateWorld();
	icon[0]->UpdateWorld();
	icon[1]->UpdateWorld();

}

void PlayerUI::PostRender()
{
	icon[0]->Render();
	icon[1]->Render();
	buttonQuad->Render();
}

void PlayerUI::GUIRender()
{
	buttonQuad->GUIRender();
	icon[0]->GUIRender();
	icon[1]->GUIRender();
}
