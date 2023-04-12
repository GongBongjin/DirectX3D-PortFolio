#include "Framework.h"

Inventory::Inventory(float& dmg, float& defenceValue, float& curHp, float& maxHp, float& hpRecoveryValue, float& curMp, float& maxMp, float& mpRecoveryValue, float& moveSpeed)
	:dmg(dmg), defenceValue(defenceValue), curHp(curHp), maxHp(maxHp), hpRecoveryValue(hpRecoveryValue), curMp(curMp), maxMp(maxMp), mpRecoveryValue(mpRecoveryValue), moveSpeed(moveSpeed)
{
	CreateInventoryPanel();

	CreateStoreItem();
}

Inventory::~Inventory()
{
	delete inventoryPanel;
	delete xButton;
	delete buyButton;
	delete undoButton;

	for (Item* storeItem : storeItems)
		delete storeItem;

	for (Item* invenItem : invenItems)
		delete invenItem;
}

void Inventory::Update()
{
	if (KEY_DOWN('I'))
		isOn = !isOn;

	inventoryPanel->UpdateWorld();
	xButton->Update();
	buyButton->Update();
	undoButton->Update();

	for (Item* storeItem : storeItems)
		storeItem->Update();

	if (!invenItems.empty())
	{
		for (Item* invenItem : invenItems)
			invenItem->Update();
	}

	if(!quickslotItems.empty())
	{
		for (Quad* quickItem : quickslotItems)
			quickItem->UpdateWorld();
	}
}

void Inventory::PreRender()
{
}

void Inventory::PostRender()
{
	if (isOn)
	{
		inventoryPanel->Render();
		xButton->Render();
		buyButton->Render();
		undoButton->Render();

		for (Item* storeItem : storeItems)
			storeItem->Render();

		if (!invenItems.empty())
		{
			for (Item* invenItem : invenItems)
			{
				invenItem->Render();
			}
		}
		//renderTarget->Set(depthStencil);
		//characterViewQuad->Render();
		FontSet();
	}

	for (Quad* quickItem : quickslotItems)
		quickItem->Render();

	for (int i = 0; i < invenItems.size(); i++)
	{
		if (invenItems[i]->GetData().key == 103 || invenItems[i]->GetData().key == 104) continue;

		if (invenItems[i]->GetCount() >= 1)
			Font::Get()->RenderText(to_string(invenItems[i]->GetCount()), { 932.0f + (i * 45), 31.0f });
	}
}

void Inventory::GUIRender()
{
	inventoryPanel->GUIRender();
	xButton->GUIRender();
	buyButton->GUIRender();
	undoButton->GUIRender();

	for (Item* storeItem : storeItems)
		storeItem->GUIRender();

	if (!invenItems.empty())
	{
		for (Item* invenItem : invenItems)
			invenItem->GUIRender();
	}
	if(!quickslotItems.empty())
	{
		for (Quad* quickItem : quickslotItems)
			quickItem->GUIRender();
	}
}

void Inventory::FontSet()
{
	Font::Get()->RenderText(PrintFloat(dmg), { 465.0f, 548.0f });
	Font::Get()->RenderText("1.0", { 468.0f, 520.0f });
	Font::Get()->RenderText(PrintFloat(defenceValue), { 465.0f, 408.0f });
	Font::Get()->RenderText(PrintFloat(curHp), { 392.0f, 380.0f });
	Font::Get()->RenderText(" / " + PrintFloat(maxHp), {472.0f, 380.0f});
	Font::Get()->RenderText(PrintFloat(curMp), { 392.0f, 352.0f });
	Font::Get()->RenderText(" / " + PrintFloat(maxMp), { 472.0f, 352.0f });
	Font::Get()->RenderText(PrintFloat(hpRecoveryValue), { 465.0f, 324.0f });
	Font::Get()->RenderText(PrintFloat(mpRecoveryValue), { 465.0f, 296.0f});
	Font::Get()->RenderText(PrintFloat(moveSpeed), { 465.0f, 187.0f });

	for(int i = 0; i<invenItems.size(); i++)
	{
		if (invenItems[i]->GetData().key == 103 || invenItems[i]->GetData().key == 104) continue;

		if(invenItems[i]->GetCount()>=1)
			Font::Get()->RenderText(to_string(invenItems[i]->GetCount()), { 860.0f + (i * 45), 257.0f });

	}

	Font::Get()->RenderText(to_string(gold), { 1030.0f, 215.0f });
}

void Inventory::CreateInventoryPanel()
{
	inventoryPanel = new Quad(L"Textures/UI/BasicQuad.png");
	inventoryPanel->SetTag("BasiceQuad");
	inventoryPanel->Load();

	xButton = new Button(L"Textures/UI/Cancel.png");
	xButton->SetTag("X");
	xButton->Load();
	xButton->SetEvent(bind(&Inventory::CloseInven, this));

	buyButton = new Button(L"Textures/UI/buyButton.png");
	buyButton->SetTag("BuyButton");
	buyButton->Load();

	undoButton = new Button(L"Textures/UI/undoButton.png");
	undoButton->SetTag("undoButton");
	undoButton->Load();
}

void Inventory::CreateStoreItem()
{
	map<UINT, ItemData> itemDatas = DataManager::Get()->GetItemDatas();

	for (pair<UINT, ItemData> itemData : itemDatas)
	{
		Item* item = new Item(itemData.second);

		item->SetTag("item" + to_string(itemData.second.key));
		item->Load();
		item->SetParamEvent(bind(&Inventory::OnSelectItem, this, item));
		item->SetObject(item);

		storeItems.push_back(item);
	}
}

void Inventory::CloseInven()
{
	isOn = !isOn;
}

void Inventory::OnSelectItem(void* selectItem)
{
	buyButton->SetObject(selectItem);

	for (Item* storeItem : storeItems)
	{
		if (selectItem == storeItem)
			storeItem->SetSelected(true);
		else
			storeItem->SetSelected(false);
	}
}

void Inventory::OnSelectInvenItem(void* selectItem)
{
	undoButton->SetObject(selectItem);

	for (Item* invenItem : invenItems)
	{
		if (selectItem == invenItem)
			invenItem->SetSelected(true);
		else
			invenItem->SetSelected(false);
	}
}

void Inventory::GetItem(void* selectItem)
{
	if (selectItem == nullptr) return;

	int itemCount = invenItems.size();
	ItemData data;

	data = ((Item*)selectItem)->GetData();

	if (gold < data.price) return;

	gold -= data.price;

	Item* newItem = new Item(data);
	Quad* quicksloatItem = new Quad(L"Textures/UI/"+data.fileName);

	if(!invenItems.empty())
	{
		for (Item* invenItem : invenItems)
		{
			if (invenItem->GetData().key == newItem->GetData().key)
			{
				if (newItem->GetData().key == 103 || newItem->GetData().key == 104)
				{
					gold += data.price;
					return;
				}

				invenItem->GetCount()++;
				return;
			}
		}
		newItem->Pos() = { 847.0f + (itemCount * 45) , 262.0f };
		newItem->SetParamEvent(bind(&Inventory::OnSelectInvenItem, this, newItem));
		invenItems.push_back(newItem);

		quicksloatItem->Pos() = { (919.0f + itemCount * 45), 36.0f };
		quickslotItems.push_back(quicksloatItem);
	}
	else
	{
		newItem->Pos() = { 847.0f + (itemCount * 45) , 262.0f };
		newItem->SetParamEvent(bind(&Inventory::OnSelectInvenItem, this, newItem));
		invenItems.push_back(newItem);

		quicksloatItem->Pos() = { (919.0f + itemCount * 45), 36.0f };
		quickslotItems.push_back(quicksloatItem);
	}
	
}

void Inventory::UndoItem(void* selectItem)
{
	if (selectItem == nullptr) return;

	for (Item* invenItem : invenItems)
	{
		if (((Item*)selectItem)->GetData().key == invenItem->GetData().key)
		{
			if (invenItem->GetCount() <= 1)
			{
				invenItems.erase(remove(invenItems.begin(), invenItems.end(), invenItem), invenItems.end());
			}

			invenItem->GetCount()--;
			gold += invenItem->GetData().price;
			return;
		}
	}

	//for (Quad* quickslotItem : quickslotItems)
	//{
	//	if (((Item*)selectItem)->GetData().fileName == L"Textures/UI/" + quickslotItem->GetFileName())
	//	{
	//		if (invenItem->GetCount() <= 1)
	//		{
	//			invenItems.erase(remove(invenItems.begin(), invenItems.end(), invenItem), invenItems.end());
	//		}
}

void Inventory::UseItem(void* selectItem)
{
	for (Item* invenItem : invenItems)
	{
		if (((Item*)selectItem)->GetData().key == invenItem->GetData().key)
		{
			if (invenItem->GetCount() <= 1)
			{
				invenItems.erase(remove(invenItems.begin(), invenItems.end(), invenItem), invenItems.end());
				//quickslotItems.erase(remove(quickslotItems.begin(), quickslotItems.end(), invenItem), quickslotItems.end());
			}
			invenItem->GetCount()--;
			return;
		}
	}
}

//아이템 사용 혹은 undo 시에 퀵슬롯 쿼드 내용 삭제 해야함