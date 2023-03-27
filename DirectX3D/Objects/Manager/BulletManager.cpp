#include "Framework.h"

BulletManager::BulletManager()
{
	bulletInstancing = new ModelInstancing("Bullet");

	bullets.reserve(SIZE);
	for (UINT i = 0; i < SIZE; i++)
	{
		Transform* transform = bulletInstancing->Add();
		transform->SetActive(false);
		Bullet* bullet = new Bullet(transform);
		bullets.push_back(bullet);
	}
}

BulletManager::~BulletManager()
{
	delete bulletInstancing;

	for (Bullet* bullet : bullets)
		delete bullet;
}

void BulletManager::Update()
{
	bulletInstancing->Update();

	for (Bullet* bullet : bullets)
		bullet->Update();
}

void BulletManager::Render()
{
	bulletInstancing->Render();

	for (Bullet* bullet : bullets)
		bullet->Render();
}

void BulletManager::GUIRender()
{
	for (Bullet* bullet : bullets)
	{
		//bullet->GetTransform()->GUIRender();
		bullet->GUIRender();
	}
}

void BulletManager::Shoot(Vector3 pos, Vector3 dir)
{
	for (Bullet* bullet : bullets)
	{
		if (!bullet->GetTransform()->Active())
		{
			bullet->Shoot(pos, dir);
			return;
		}
	}
}

bool BulletManager::IsCollision(Collider* collider)
{
	for (Bullet* bullet : bullets)
	{
		if (bullet->GetCollider()->IsCollision(collider))
		{
			bullet->GetTransform()->SetActive(false);
			return true;
		}
	}
	return false;
}
