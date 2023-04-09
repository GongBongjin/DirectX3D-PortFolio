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
	bool isOn = false;

	Quad* quad;
	Quad* xQuad;
	vector<Quad*> itemIcons;

	RenderTarget* renderTarget;
	DepthStencil* depthStencil;
	Quad* depQuad;

	float maxHp;
	UINT gold;
};