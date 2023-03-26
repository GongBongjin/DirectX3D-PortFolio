#include "Framework.h"

EnemyManager::EnemyManager()
{
	enemies.reserve(3);

	enemyInstancing[0] = new ModelAnimatorInstancing("First");
	enemyInstancing[0]->ReadClip("Idle");
	for (int i = 0; i < 1; i++)
	{
		Transform* transform = enemyInstancing[0]->Add();
		transform->Scale() = { 0.02f, 0.02f, 0.02f };
		//transform->Rot().y = 180.0f;
		transform->SetActive(false);
		MinionFirst* first = new MinionFirst(transform, enemyInstancing[0], i);
		enemies.push_back(first);
	}

	enemyInstancing[1] = new ModelAnimatorInstancing("Second");
	enemyInstancing[1]->ReadClip("Idle");
	for (int i = 0; i < 1; i++)
	{
		Transform* transform = enemyInstancing[1]->Add();
		transform->Scale() = { 0.02f, 0.02f, 0.02f };
		//transform->Rot().y = 180.0f;
		transform->SetActive(false);
		MinionSecond* second = new MinionSecond(transform, enemyInstancing[1], i);
		enemies.push_back(second);
	}

	enemyInstancing[2] = new ModelAnimatorInstancing("Super");
	enemyInstancing[2]->ReadClip("Idle");
	for (int i = 0; i < 1; i++)
	{
		Transform* transform = enemyInstancing[2]->Add();
		transform->Scale() = { 0.02f, 0.02f, 0.02f };
		//transform->Rot().y = 180.0f;
		transform->SetActive(false);
		MinionSuper* super = new MinionSuper(transform, enemyInstancing[2], i);
		enemies.push_back(super);
	}
}

EnemyManager::~EnemyManager()
{
	delete enemyInstancing[0];
	delete enemyInstancing[1];
	delete enemyInstancing[2];
	
	for (Enemy* enemy : enemies)
		delete enemy;
}

void EnemyManager::Update()
{
	spawnTime += DELTA;

	if (spawnTime > SPAWN_TIME)
	{
		spawnTime -= SPAWN_TIME;
		Spawn();
	}

	enemyInstancing[0]->Update();
	enemyInstancing[1]->Update();
	enemyInstancing[2]->Update();
	
	for (Enemy* enemy : enemies)
		enemy->Update();
}

void EnemyManager::Render()
{
	enemyInstancing[0]->Render();
	enemyInstancing[1]->Render();
	enemyInstancing[2]->Render();
	
	for (Enemy* enemy : enemies)
		enemy->Render();

}

void EnemyManager::PostRender()
{
}

void EnemyManager::GUIRender()
{
	for (Enemy* enemy : enemies)
	{
		enemy->GetTransform()->GUIRender();
		enemy->GUIRender();
	}
}

void EnemyManager::SetTarget(Transform* target)
{
	this->target = target;

	for (Enemy* enemy : enemies)
		enemy->SetTarget(target);
}

void EnemyManager::IsCollision()
{
}

void EnemyManager::Spawn()
{
	Vector3 dir;
	dir.x = Random(-10.0f, 10.0f);
	dir.z = Random(-10.0f, 10.0f);

	Vector3 randomPos = Vector3::One() + dir.GetNormalized() * 5.0f;

	for (Enemy* enemy : enemies)
	{
		if (!enemy->GetTransform()->Active())
		{
			enemy->Spawn(randomPos);
			break;
		}
	}
}
