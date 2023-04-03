#include "Framework.h"

BuildingManager::BuildingManager()
{
	CreateBuilding();
}

BuildingManager::~BuildingManager()
{
	for (Building* building : buildings)
		delete building;
}

void BuildingManager::Update()
{
	for (Building* building : buildings)
		building->Update();
}

void BuildingManager::Render()
{
	for (Building* building : buildings)
		building->Render();
}

void BuildingManager::GUIRender()
{
	for (Building* building : buildings)
		building->GUIRender();
}

void BuildingManager::CreateBuilding()
{
	buildings.resize(6);
	colliders.reserve(6);

	vector<string> s = { {"B0"}, {"B1"}, {"B2"}, {"B3"}, {"B4"}, {"B5"}, {"B6"} };

	int i = 0;
	
	for (Building*& building : buildings)
	{
		building = new Building(s[i]);
		building->SetTag(s[i]);
		building->Rot().x = XM_PIDIV2;
		building->Load();
		building->Update();
		colliders.push_back(building->GetCollider());
		i++;
	}

	i = 0;
}
