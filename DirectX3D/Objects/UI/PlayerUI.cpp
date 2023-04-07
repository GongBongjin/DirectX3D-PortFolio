#include "Framework.h"

PlayerUI::PlayerUI()
{
	icon[0] = new Quad(L"Textures/UI/Attack.png");
	icon[0]->SetTag("attackIcon");
	icon[0]->Load();

	icon[1] = new Quad(L"Textures/UI/Reload.png");
	icon[1]->SetTag("reloadIcon");
	icon[1]->Load();

	icon[2] = new Quad(L"Textures/UI/PlayerIcon.png");
	icon[2]->SetTag("playerIcon");
	icon[2]->Load();

	buttonQuad = new Quad(L"Textures/UI/Revenant_AttackUI.png");
	buttonQuad->SetTag("quad");
	buttonQuad->Load();

	barFrame = new Quad(L"Textures/UI/BarFrame.png");
	barFrame->SetTag("barFrame");
	barFrame->Load();
	progressBar[0] = new ProgressBar(L"Textures/UI/hp_bar1.png", L"Textures/UI/hp_bar_BG.png");
	progressBar[0]->SetTag("Hpbar");
	progressBar[0]->Load();
	progressBar[1] = new ProgressBar(L"Textures/UI/hp_bar2.png", L"Textures/UI/hp_bar_BG.png");
	progressBar[1]->SetTag("Mpbar");
	progressBar[1]->Load();

	inventory = new Inventory();
}

PlayerUI::~PlayerUI()
{
	delete buttonQuad;
	delete icon[0];
	delete icon[1];
	delete icon[2];

	delete barFrame;
	delete progressBar[0];
	delete progressBar[1];

	delete inventory;
}


void PlayerUI::Update()
{
	buttonQuad->UpdateWorld();
	icon[0]->UpdateWorld();
	icon[1]->UpdateWorld();
	icon[2]->UpdateWorld();

	barFrame->UpdateWorld();

	progressBar[0]->SetAmount(testp);
	progressBar[0]->UpdateWorld();
	progressBar[1]->UpdateWorld();

	inventory->GetPlayerInfo(maxHp, gold);
	inventory->Update();
}

void PlayerUI::PostRender()
{
	icon[0]->Render();
	icon[1]->Render();
	icon[2]->Render();
	buttonQuad->Render();

	barFrame->Render();
	progressBar[0]->Render();
	progressBar[1]->Render();
	inventory->PostRender();

	Font::Get()->RenderText(to_string((UINT)curHp) + " / " + to_string((UINT)maxHp), { CENTER_X, 50});
}

void PlayerUI::GUIRender()
{
	buttonQuad->GUIRender();
	icon[0]->GUIRender();
	icon[1]->GUIRender();
	icon[2]->GUIRender();

	barFrame->GUIRender();
	progressBar[0]->GUIRender();
	progressBar[1]->GUIRender();
	inventory->GUIRender();
}

void PlayerUI::GetPlayerInfo(float curHp, float maxHp, UINT gold)
{
	this->curHp = curHp;
	this->maxHp = maxHp;
	this->gold = gold;

	testp =  curHp / maxHp;
}
