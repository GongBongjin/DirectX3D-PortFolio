#pragma once

class Bullet
{
private:
	const float LIFE_TIME = 5.0f;
public:
	Bullet(Transform* transform);
	~Bullet();

	void Update();
	void Render();
	void GUIRender();

	void Shoot(Vector3 pos, Vector3 dir);

	CapsuleCollider* GetCollider() { return collider; }
	Transform* GetTransform() { return transform; }

private:
	Transform* transform;
	CapsuleCollider* collider;

	Vector3 direction;

	float speed = 50.0f;
	float time = 0.0f;
};