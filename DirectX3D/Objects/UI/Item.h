#pragma once

class Item : public Button
{
public:
	Item(ItemData itemData);
	~Item();

	void Update();
	void Render();
	void GUIRender();

	void SetSelected(bool isSelected) { this->isSelected = isSelected; }

	ItemData GetData() { return itemData; }
	int& GetCount() { return count; }
private:
	ItemData itemData;

	int count = 1;

	bool isSelected;
};