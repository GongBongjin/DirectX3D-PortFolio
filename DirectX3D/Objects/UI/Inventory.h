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
	Button* GetBuyButton() { return buyButton; }
	Button* GetUndoButton() { return undoButton; }
	vector<Item*>& GetInvenItemData() { return invenItems; }
	
private:
	void CreateInventoryPanel();
	void CreateStoreItem();

	void CloseInven();
	void OnSelectItem(void* selectItem);

private:
	bool isOn = false;

	Quad* inventoryPanel;
	Button* xButton;

	Button* buyButton;
	Button* undoButton;
	vector<Item*> storeItems;
	
	vector<Item*> invenItems;
	//ItemData data;
	
	RenderTarget* renderTarget;
	DepthStencil* depthStencil;
	Quad* characterViewQuad;

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