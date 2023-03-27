#include "Framework.h"

Bullet::Bullet(Transform* transform)
	:transform(transform)
{
	transform->Scale() = { 0.1f,0.1f,0.1f };
	transform->Load();

	collider = new CapsuleCollider();
	collider->SetParent(transform);
	collider->Scale() = { 0.8f, 0.8f, 0.8f };
	collider->Rot().x = XM_PIDIV2;
	collider->Rot().y = XM_PIDIV2;
	collider->SetTag("B_Collider");
}

Bullet::~Bullet()
{
	delete collider;
}

void Bullet::Update()
{
	if (!transform->Active()) return;
	
	time += DELTA;
	
	if (time > LIFE_TIME)
		transform->SetActive(false);
	
	transform->Pos() += direction * speed * DELTA;

	collider->UpdateWorld();
}

void Bullet::Render()
{
	collider->Render();
}

void Bullet::GUIRender()
{
	collider->GUIRender();
}

void Bullet::Shoot(Vector3 pos, Vector3 dir)
{
	transform->SetActive(true);

	transform->Pos() = pos;
	direction = dir;

	transform->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2;

	time = 0.0f;
}
