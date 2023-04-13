#include "Framework.h"

Bullet::Bullet(Transform* transform)
	:transform(transform)
{
	transform->Scale() = { 0.3f,0.3f,0.3f };
	//transform->Load();

	collider = new CapsuleCollider();
	collider->SetParent(transform);
	collider->Scale() = { 0.8f, 0.8f, 0.8f };
	collider->Rot().x = XM_PIDIV2;
	collider->Rot().y = XM_PIDIV2;
	collider->SetTag("B_Collider");

	startEdge = new Transform();

	endEdge = new Transform();

	trail = new Trail(L"Textures/Effect/FireTrail0.png", startEdge, endEdge, 1, 10.0f);
	//trail->SetParent(transform);
}

Bullet::~Bullet()
{
	delete collider;

	delete trail;

	delete startEdge;
	delete endEdge;
}

void Bullet::Update()
{
	if (!transform->Active()) return;
	
	time += DELTA;
	
	if (time > LIFE_TIME)
	{
		transform->SetActive(false);
		trail->SetActive(false);
	}
	
	transform->Pos() += direction * speed * DELTA;

	collider->UpdateWorld();

	startEdge->Pos() = transform->GlobalPos() + transform->Right() * 2.0f;
	endEdge->Pos() = transform->GlobalPos() - transform->Right() * 2.0f;

	startEdge->UpdateWorld();
	endEdge->UpdateWorld();

	trail->Update();
}

void Bullet::Render()
{
	collider->Render();

	trail->Render();
}

void Bullet::GUIRender()
{
	collider->GUIRender();
}

void Bullet::Shoot(Vector3 pos, Vector3 dir)
{
	transform->SetActive(true);
	trail->SetActive(true);

	transform->Pos() = pos;
	trail->Pos() = pos;

	trail->SetPos(pos);
	transform->UpdateWorld();
	trail->UpdateWorld();

	direction = dir;

	transform->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2;

	time = 0.0f;
}
