#include "Framework.h"

Enemy::Enemy(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	:transform(transform), instancing(instancing), index(index)
{
	motion = instancing->GetMotion(index);
	totalEvent.resize(instancing->GetClipSize());
	eventIters.resize(instancing->GetClipSize());
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (!transform->Active()) return;

	velocity = target->GlobalPos() - transform->GlobalPos();

	Move();

	collider->UpdateWorld();
}

void Enemy::Render()
{
	collider->Render();
}

void Enemy::PostRender()
{
}

void Enemy::Spawn(Vector3 pos)
{
	transform->SetActive(true);
	collider->SetActive(true);

	SetState(IDLE);

	curHp = maxHp;

	transform->Pos() = pos;
}

void Enemy::Hitted()
{
	transform->SetActive(false);
	collider->SetActive(false);
}

void Enemy::SetState(State state)
{
	if (curState == state) return;

	curState = state;
	instancing->PlayClip(index, state);
	eventIters[state] = totalEvent[state].begin();
}

void Enemy::Move()
{
	if (!transform->Active()) return;
	if (velocity.Length() < 2.0f) return;

	if (velocity.Length() < 100.0f)
	{
		SetState(MOVE);
	}

	transform->Pos() += velocity.GetNormalized() * speed * DELTA;
	transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
}
