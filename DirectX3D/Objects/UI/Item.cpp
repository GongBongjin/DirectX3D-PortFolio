#include "Framework.h"

Item::Item(wstring textureFile)
	:Button(textureFile)
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
