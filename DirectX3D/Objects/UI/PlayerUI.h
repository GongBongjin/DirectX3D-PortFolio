#pragma once

class PlayerUI
{
public:
	PlayerUI();
	~PlayerUI();

	void Update();
	void PostRender();
	void GUIRender();


private:
	Quad* buttonQuad;
	Quad* icon[2];
};