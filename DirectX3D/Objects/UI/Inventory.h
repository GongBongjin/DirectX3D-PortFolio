#pragma once

class Inventory
{
public:
	Inventory();
	~Inventory();

	void Update();
	void PostRender();
	void GUIRender();

	void GetPlayerInfo(float maxHp, UINT gold);
	void FontSet();

private:
	bool isOn = false;

	Quad* quad;
	Quad* abilityQuad;
	Quad* invenQuad;
	vector<Quad*> rooms;

	vector<UINT> fontdata;

	float maxHp;
	UINT gold;
};