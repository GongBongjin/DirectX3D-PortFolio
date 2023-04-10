#pragma once

struct ItemData
{
	string name;
	UINT price;
};

class Item : public Button
{
public:
	Item(wstring textureFile);
	~Item();

	void Update();
	void Render();
	void GUIRender();

	void SetSelected(bool selected) { isSelected = selected; }

private:
	ItemData* itemData;

	bool isSelected;
};