#pragma once

class BulletManager : public Singleton<BulletManager>
{
private:
	const UINT SIZE = 8;

public:
	BulletManager();
	~BulletManager();

	void Update();
	void Render();
	void GUIRender();

	void Shoot(Vector3 pos, Vector3 dir);

	bool IsCollision(Collider* collider);

private:
	ModelInstancing* bulletInstancing;
	vector<Bullet*> bullets;

};