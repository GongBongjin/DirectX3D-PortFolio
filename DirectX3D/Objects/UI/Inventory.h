#pragma once

class Inventory
{
public:
	Inventory(float& dmg, float& defenceValue, float& curHp, float& maxHp, float& hpRecoveryValue,
		float& curMp, float& maxMp, float& mpRecoveryValue, float& moveSpeed);
	~Inventory();

	void Update();
	void PreRender();
	void PostRender();
	void GUIRender();

	void FontSet();

	bool& isUIOn() { return isOn; }

	void GetItem(void* selectItem);
	void UndoItem(void* selectItem);
	void UseItem(void* selectItem);
	
	UINT GetGold(UINT gold) { return this->gold += gold; }

	Button* GetBuyButton() { return buyButton; }
	Button* GetUndoButton() { return undoButton; }
	vector<Item*>& GetInvenItemData() { return invenItems; }
	
private:
	void CreateInventoryPanel();
	void CreateStoreItem();

	void CloseInven();
	void OnSelectItem(void* selectItem);
	void OnSelectInvenItem(void* selectItem);

private:
	bool isOn = false;

	Quad* inventoryPanel;
	Button* xButton;

	Button* buyButton;
	Button* undoButton;
	vector<Item*> storeItems;
	
	vector<Item*> invenItems;
	vector<Quad*> quickslotItems;

	UINT gold = 1000;

	float& dmg;
	float& defenceValue;

	float& curHp;
	float& maxHp;
	float& hpRecoveryValue;

	float& curMp;
	float& maxMp;
	float& mpRecoveryValue;

	float& moveSpeed;
};