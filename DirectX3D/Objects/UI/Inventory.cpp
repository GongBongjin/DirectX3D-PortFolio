#include "Framework.h"

Inventory::Inventory()
{
	quad = new Quad(L"Textures/UI/BasicQuad.png");
	quad->SetTag("BasiceQuad");
	quad->Load();

	abilityQuad = new Quad(L"Textures/UI/ability.png");
	abilityQuad->SetTag("ability_Quad");
	abilityQuad->Load();

	invenQuad = new Quad(L"Textures/UI/inven.png");
	invenQuad->SetTag("inven_Quad");
	invenQuad->Load();

	rooms.resize(5);
	int i = 0;
	for (Quad*& room : rooms)
	{
		room = new Quad(L"Textures/UI/roomFrame.png");
		room->SetTag("room"+ to_string(i));
		room->Pos() = { (float)1094 - (i * 38), 197.0f, 0.0f };
		room->Scale() = { 0.7f, 0.7f, 0 };

		i++;
	}
	
	i = 0;
}

Inventory::~Inventory()
{
	delete quad;
	delete abilityQuad;
	delete invenQuad;

	for (Quad* room : rooms)
		delete room;
}

void Inventory::Update()
{
	if (KEY_DOWN('I'))
		isOn = !isOn;

	quad->UpdateWorld();
	abilityQuad->UpdateWorld();
	invenQuad->UpdateWorld();

	for (Quad* room : rooms)
		room->UpdateWorld();
}

void Inventory::PostRender()
{
	if (!isOn) return;

	quad->Render();

	abilityQuad->Render();

	invenQuad->Render();

	for (Quad* room : rooms)
		room->Render();

	FontSet();
}

void Inventory::GUIRender()
{
	quad->GUIRender();
	
	abilityQuad->GUIRender();

	invenQuad->GUIRender();

	for (Quad* room : rooms)
		room->GUIRender();
}

void Inventory::GetPlayerInfo(float maxHp, UINT gold)
{
	this->maxHp = maxHp;
	this->gold = gold;
}

void Inventory::FontSet()
{
	Float2 pos;

	//Font::Get()->RenderText("Attack", { 250.0f, 600.0f });
	//Font::Get()->RenderText("물리 공격력", { 320.0f, 570.0f });
	//Font::Get()->RenderText("마법 공격력", { 320.0f, 550.0f });
	//Font::Get()->RenderText("공격 속도", { 300.0f, 530.0f });
	//Font::Get()->RenderText("Defence", { 260.0f, 400.0f });
	//Font::Get()->RenderText("물리 방어력", { CENTER_X, 175.0f});
	//Font::Get()->RenderText("마법 방어력", { CENTER_X, 170.0f });
	//Font::Get()->RenderText("체력", { CENTER_X, 165.0f });
	//Font::Get()->RenderText("체력 재생", { CENTER_X, 160.0f });
	//Font::Get()->RenderText("마나", { CENTER_X, 155.0f });
	//Font::Get()->RenderText("마나 재생", { CENTER_X, 150.0f });
	//Font::Get()->RenderText("이동 속도", { CENTER_X, 150.0f });

	Font::Get()->RenderText(to_string(gold), { 880.0f, 201.0f });
}
