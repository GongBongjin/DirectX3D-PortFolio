#pragma once

class BuildingManager : public Singleton<BuildingManager>
{
public:
	BuildingManager();
	~BuildingManager();

	void Update();
	void Render();
	void GUIRender();

	vector<BoxCollider*> GetColliders() { return colliders; }
private:
	void CreateBuilding();

private:
	vector<Building*> buildings;
	vector<BoxCollider*> colliders;
};