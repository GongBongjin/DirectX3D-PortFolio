#include "Framework.h"

Enemy::Enemy(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	:transform(transform), instancing(instancing), index(index)
{
	motion = instancing->GetMotion(index);
	totalEvent.resize(instancing->GetClipSize());
	eventIters.resize(instancing->GetClipSize());

	SetEvent(ATTACK, bind(&Enemy::ComboAttack, this), 0.9f);
	SetEvent(ATTACK1, bind(&Enemy::SetIdle, this), 0.9f);
	SetEvent(HITTED, bind(&Enemy::SetIdle, this), 0.9f);
	SetEvent(DYING, bind(&Enemy::EndDyingDC, this), 0.0f);
	SetEvent(DYING, bind(&Enemy::EndDyingDT, this), 1.0f);
	
	FOR(totalEvent.size())
	{
		eventIters[i] = totalEvent[i].begin();
	}
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (!transform->Active()) return;

	velocity = target->GlobalPos() - transform->GlobalPos();

	ExcuteEvent();
	Move();
	Attack();
	Dead();

	collider->UpdateWorld();
}

void Enemy::Render()
{
	if (!transform->Active()) return;

	collider->Render();
}

void Enemy::PostRender()
{
}

void Enemy::Spawn(Vector3 pos)
{
	//if (curState == DYING) return;

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

void Enemy::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvent[clip].count(timeRatio) > 0)
		return;

	totalEvent[clip][timeRatio] = event;
}

void Enemy::ExcuteEvent()
{
	int index = curState;

	if (totalEvent[index].empty()) return;
	if (eventIters[index] == totalEvent[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}

void Enemy::Move()
{
	if (!transform->Active()) return;
	if (velocity.Length() < attackRange) return;
	if (curState == ATTACK) return;
	if (curState == ATTACK1) return;
	if (curState == HITTED) return;
	if (curState == DYING) return;

	if (velocity.Length() < chaseRange)
	{
		SetState(MOVE);
	}

	transform->Pos() += velocity.GetNormalized() * speed * DELTA;
	transform->Rot().y = atan2(velocity.x, velocity.z);
}

void Enemy::Attack()
{
	if (!transform->Active()) return;
	if (velocity.Length() >= attackRange) return;
	if (curState == ATTACK) return;
	if (curState == ATTACK1) return;
	if (curState == HITTED) return;
	if (curState == DYING) return;

	SetState(ATTACK);
}

void Enemy::Dead()
{
	if (!transform->Active()) return;
	if (curState == DYING) return;
	if (curHp > 0) return;

	if (curHp <= 0)
		SetState(DYING);
}

void Enemy::ComboAttack()
{
	if (curState == HITTED) return;

	SetState(ATTACK1);
}

void Enemy::SetIdle()
{
	SetState(IDLE);
}

void Enemy::Hitted()
{
	if (curState == DYING) return;

	SetState(HITTED);
	curHp -= 100.0f;
}

void Enemy::EndDyingDC()
{
	collider->SetActive(false);
}

void Enemy::EndDyingDT()
{
	transform->SetActive(false);
}
