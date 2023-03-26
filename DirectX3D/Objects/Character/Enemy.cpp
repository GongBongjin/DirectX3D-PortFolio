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

void Enemy::SetState(State state)
{
	if (curState == state) return;

	curState = state;
	instancing->PlayClip(index, state);
	eventIters[state] = totalEvent[state].begin();
}
