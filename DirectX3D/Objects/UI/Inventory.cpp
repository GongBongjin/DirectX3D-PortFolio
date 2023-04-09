#include "Framework.h"

Inventory::Inventory()
{
	quad = new Quad(L"Textures/UI/BasicQuad.png");
	quad->SetTag("BasiceQuad");
	quad->Load();

	xQuad = new Quad(L"Textures/UI/Cancel.png");
	xQuad->SetTag("X");
	xQuad->Load();

	renderTarget = new RenderTarget();
	depthStencil = new DepthStencil();
	depQuad = new Quad(L"Textures/UI/RenderTargetQuad.png");
	depQuad->GetMaterial()->SetShader(L"Effect/Bloom.hlsl");
	depQuad->GetMaterial()->SetDiffuseMap(Texture::Add(L"Test", renderTarget->GetSRV()));
	depQuad->SetTag("depQuad");
	depQuad->Load();
	

	vector<wstring> iconName = { {L"hp.png"}, {L"mp.png"}, {L"bow.png"}, {L"helmets.png"} };
	itemIcons.resize(iconName.size());
	for (UINT i = 0; i < itemIcons.size(); i++)
	{
		itemIcons[i] = new Quad(L"Textures/UI/" + iconName[i]);
		itemIcons[i]->SetTag("icon" + to_string(i));
		itemIcons[i]->Load();
	}
}

Inventory::~Inventory()
{
	delete quad;

	delete xQuad;

	for (Quad* itemIcon : itemIcons)
		delete itemIcon;

	delete renderTarget;
	delete depthStencil;

	delete depQuad;
}

void Inventory::Update()
{
	if (KEY_DOWN('I'))
		isOn = !isOn;

	IsClick();

	quad->UpdateWorld();

	depQuad->UpdateWorld();

	xQuad->UpdateWorld();

	for (Quad* itemIcon : itemIcons)
		itemIcon->UpdateWorld();
}

void Inventory::PostRender()
{
	if (!isOn) return;

	quad->Render();

	depQuad->Render();

	xQuad->Render();


	for (Quad* itemIcon : itemIcons)
		itemIcon->Render();

	FontSet();

	//renderTarget->Set(depthStencil);
}

void Inventory::GUIRender()
{
	quad->GUIRender();

	depQuad->GUIRender();

	xQuad->GUIRender();

	for (Quad* itemIcon : itemIcons)
		itemIcon->GUIRender();
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

	Font::Get()->RenderText(to_string(gold), { 1030.0f, 215.0f });
}