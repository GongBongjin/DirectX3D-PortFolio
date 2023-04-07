#pragma once

class PlayerUI
{
public:
	PlayerUI();
	~PlayerUI();

	void Update();
	void PostRender();
	void GUIRender();

	void GetPlayerInfo(float curHp, float maxHp, UINT gold);

private:
	Quad* buttonQuad;
	Quad* icon[3];
	Quad* barFrame;
	ProgressBar* progressBar[2];
	Inventory* inventory;

	float testp;
	float curHp;
	float maxHp;
	UINT gold;
};