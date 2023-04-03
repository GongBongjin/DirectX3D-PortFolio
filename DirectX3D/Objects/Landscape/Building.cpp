#include "Framework.h"

Building::Building(string name)
	:Model(name)
{
	collider = new BoxCollider();
	collider->SetTag(name + "collider");
	collider->SetParent(this);
	collider->Load();
}

Building::~Building()
{
	delete collider;
}

void Building::Update()
{
	Model::UpdateWorld();

	collider->UpdateWorld();	
}

void Building::Render()
{
	Model::Render();

	collider->Render();	
}

void Building::GUIRender()
{
	Model::GUIRender();
	collider->GUIRender();
}
