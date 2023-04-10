#pragma once

class Inventory
{
public:
	Inventory();
	~Inventory();

	void Update();
	void PreRender();
	void PostRender();
	void GUIRender();

	void GetPlayerInfo(float maxHp, UINT gold);
	void FontSet();

private:
	void CloseInven();
	void OnSelectItem(Button* button);

private:
	bool isOn = false;

	Quad* inventoryPanel;
	Button* xButton;
	vector<Button*> itemIcons;
	vector<Button*> invenIcons;
	map<UINT, vector<Button*>> inven;

	RenderTarget* renderTarget;
	DepthStencil* depthStencil;
	Quad* characterViewQuad;

	float maxHp;
	UINT gold;

	void* selectItem;
};