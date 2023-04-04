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
	SetEvent(DYING, bind(&Enemy::EndDyingDT, this), 0.9f);
	
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

	range = target->GlobalPos() - transform->GlobalPos();

	ExcuteEvent();
	test();
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

void Enemy::test()
{
	if(range.Length() < chaseRange)
	{
		destPos = target->GlobalPos();

		if (aStar->IsCollisionObstacle(transform->GlobalPos(), destPos))
		{
			SetPath();
		}
		else
		{
			path.clear();
			path.push_back(destPos);
		}
	}
}

void Enemy::Move()
{
	if (!transform->Active()) return;
	//if (range.Length() > chaseRange)
	//{
	//	SetState(IDLE);
	//	return;
	//}

	if (curState == ATTACK) return;
	if (curState == ATTACK1) return;
	if (curState == HITTED) return;
	if (curState == DYING) return;

	/*destPos = target->GlobalPos();

	if (aStar->IsCollisionObstacle(transform->GlobalPos(), destPos))
	{
		SetPath();
	}
	else
	{
		path.clear();
		path.push_back(destPos);
	}*/
	

	if (path.empty())
	{
		SetState(IDLE);
		return;
	}

	
	Vector3 dest = path.back();

	Vector3 direction = dest - transform->GlobalPos();
	direction.y = 0.0f;

	if (direction.Length() < 1.0f)
		path.pop_back();

	SetState(MOVE);

	Vector3 velocitiy = direction.GetNormalized();

	transform->Pos() += velocitiy * speed * DELTA;
	transform->Rot().y = atan2(velocitiy.x, velocitiy.z);
}

//void Enemy::Move()
//{
//	if (!transform->Active()) return;
//	if (velocity.Length() < attackRange) return;
//	if (curState == ATTACK) return;
//	if (curState == ATTACK1) return;
//	if (curState == HITTED) return;
//	if (curState == DYING) return;
//
//	if (velocity.Length() < chaseRange)
//	{
//		SetState(MOVE);
//	}
//
//	transform->Pos() += velocity.GetNormalized() * speed * DELTA;
//	transform->Rot().y = atan2(velocity.x, velocity.z);
//}

void Enemy::Attack()
{
	if (!transform->Active()) return;
	if (range.Length() > attackRange) return;
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
	if (curState == DYING) return;

	SetState(IDLE);
}

void Enemy::Hitted()
{
	if (curState == DYING) return;

	SetState(HITTED);
	curHp -= 20.0f;
}

void Enemy::EndDyingDC()
{
	collider->SetActive(false);
}

void Enemy::EndDyingDT()
{
	transform->SetActive(false);
}

void Enemy::SetPath()
{
	int startIndex = aStar->FindCloseNode(transform->GlobalPos());
	int endIndex = aStar->FindCloseNode(destPos);

	aStar->GetPath(startIndex, endIndex, path);
	aStar->MakeDirectPath(transform->GlobalPos(), destPos, path);

	UINT pathSize = path.size();

	while (path.size() > 2)
	{
		vector<Vector3> tempPath = path;
		tempPath.erase(tempPath.begin());
		tempPath.pop_back();

		Vector3 start = path.back();
		Vector3 end = path.front();

		aStar->MakeDirectPath(start, end, tempPath);
		path.clear();

		path = tempPath;
		path.insert(path.begin(), end);
		path.push_back(start);

		if (pathSize == path.size())
			break;
		else
			pathSize = path.size();
	}

	path.insert(path.begin(), destPos);
}
