#pragma once

class PlayerUI
{
public:
	PlayerUI(float& dmg, float& defenceValue, float& curHp, float& maxHp, float& hpRecoveryValue,
		float& curMp, float& maxMp, float& mpRecoveryValue, float& moveSpeed);
	~PlayerUI();

	void Update();
	void PreRender();
	void PostRender();
	void GUIRender();

	void CreateMainUI();
	void SetProgressBar();

	Inventory* GetInven() { return inventory; }

private:
	Quad* buttonQuad;
	Quad* icon[3];
	Quad* barFrame;
	Quad* quickSloatQuad;

	ProgressBar* progressBar[2];
	Inventory* inventory;

	float hpRate;
	float mpRate;

	float& curHp;
	float& maxHp;

	float& curMp;
	float& maxMp;
};