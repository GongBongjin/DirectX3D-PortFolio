#include "Framework.h"

Item::Item(ItemData itemData)
	:itemData(itemData), Button(L"Textures/UI/"+itemData.fileName)
{

}

Item::~Item()
{
}

void Item::Update()
{
	Button::Update();
}

void Item::Render()
{
	Button::Render();
}

void Item::GUIRender()
{
	Button::GUIRender();
}
