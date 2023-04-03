#pragma once

class Building : public Model
{
public:
	Building(string name);
	~Building();

	void Update();
	void Render();
	void GUIRender();

	BoxCollider* GetCollider() { return collider; }

private:
	BoxCollider* collider;

	Transform* root;
};