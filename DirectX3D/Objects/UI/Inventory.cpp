#include "Framework.h"

Inventory::Inventory()
{
	inventoryPanel = new Quad(L"Textures/UI/BasicQuad.png");
	inventoryPanel->SetTag("BasiceQuad");
	inventoryPanel->Load();

	xButton = new Button(L"Textures/UI/Cancel.png");
	xButton->SetTag("X");
	xButton->Load();
	xButton->SetEvent(bind(&Inventory::CloseInven, this));

	vector<wstring> iconName = { {L"hp.png"}, {L"mp.png"}, {L"bow.png"}, {L"helmets.png"} };
	itemIcons.resize(iconName.size());
	for (UINT i = 0; i < itemIcons.size(); i++)
	{
		itemIcons[i] = new Button(L"Textures/UI/" + iconName[i]);
		itemIcons[i]->SetTag("icon" + to_string(i));
		itemIcons[i]->SetParamEvent(bind(&Inventory::OnSelectItem, this, itemIcons[i]));
		itemIcons[i]->Load();
	}

	//invenIcons.resize(6);
	//for (UINT i = 0; i < invenIcons.size(); i++)
	//{
	//	invenIcons[i] = new Button(Vector2{5.0f, 5.0f});
	//	invenIcons[i]->SetTag("inven" + to_string(i));
	//}

	renderTarget = new RenderTarget();
	depthStencil = new DepthStencil();
	characterViewQuad = new Quad(L"Textures/UI/RenderTargetQuad.png");
	characterViewQuad->GetMaterial()->SetShader(L"Effect/Bloom.hlsl");
	characterViewQuad->GetMaterial()->SetDiffuseMap(Texture::Add(L"Test", renderTarget->GetSRV()));
	characterViewQuad->SetTag("characterViewQuad");
	characterViewQuad->Load();
}

Inventory::~Inventory()
{
	delete inventoryPanel;

	delete xButton;

	for (Button* itemIcon : itemIcons)
		delete itemIcon;

	for (Button* invenIcon : invenIcons)
		delete invenIcon;

	delete renderTarget;
	delete depthStencil;

	delete characterViewQuad;
}

void Inventory::Update()
{
	if (KEY_DOWN('I'))
		isOn = !isOn;

	inventoryPanel->UpdateWorld();

	characterViewQuad->UpdateWorld();

	xButton->Update();

	for (Button* itemIcon : itemIcons)
		itemIcon->Update();

	if (!invenIcons.empty()) return;
	{
		for (Button* invenIcon : invenIcons)
			invenIcon->Update();
	}
}

void Inventory::PreRender()
{
}

void Inventory::PostRender()
{
	if (!isOn) return;

	inventoryPanel->Render();

	//renderTarget->Set(depthStencil);
	//characterViewQuad->Render();

	xButton->Render();

	for (Button* itemIcon : itemIcons)
		itemIcon->Render();

	if(!invenIcons.empty())
	{
		for (Button* invenIcon : invenIcons)
		{
			invenIcon->Render();
		}
	}

	FontSet();
}

void Inventory::GUIRender()
{
	inventoryPanel->GUIRender();

	characterViewQuad->GUIRender();

	xButton->GUIRender();

	for (Button* itemIcon : itemIcons)
		itemIcon->GUIRender();

	if (!invenIcons.empty())
	{
		for (Button* invenIcon : invenIcons)
			invenIcon->GUIRender();
	}
}

void Inventory::GetPlayerInfo(float maxHp, UINT gold)
{
	this->maxHp = maxHp;
	this->gold = gold;
}

void Inventory::FontSet()
{
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

void Inventory::CloseInven()
{
	isOn = !isOn;
}

void Inventory::OnSelectItem(Button* button)
{
	//if(invenIcons.size() == 1)
	{
		Button* storeB = new Button(button->GetFileName());
		storeB->Pos() = {900.0f, 450.0f, 0.0f};
		storeB->UpdateWorld();
		storeB->GetCollider()->UpdateWorld();

		for (pair<UINT, vector<Button*>> item : inven)
		{

		}

		
		//invenIcons.push_back(storeB);
	}
}
