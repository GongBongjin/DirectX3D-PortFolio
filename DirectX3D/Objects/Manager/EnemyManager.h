#pragma once

class EnemyManager : public Singleton<EnemyManager>
{
private:
	const UINT COUNT = 2;
	const float SPAWN_TIME = 2.0f;

public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();

	void SetTarget(Transform* target);
	bool IsCollision(Ray ray, Vector3& hitPoint);

private:
	void Collision();
	void Spawn();

private:
	ModelAnimatorInstancing* enemyInstancing[3];
	vector<Enemy*> enemies;

	Transform* target;

	float spawnTime = 0.0f;
};