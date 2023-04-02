#pragma once

class Boss : public ModelAnimator
{
private:
	enum State
	{
		IDLE,
		ATTACK0,
		ATTACK1,
		ATTACK2,
		ATTACK3,
		MOVE,
		HITTED,
		DYING
	}curState=IDLE;

public:
	Boss();
	~Boss();

	void Update();
	void Render();
	void PostRender();
	void GUIRender();
	
private:
	void Move();
	void Attack0();
	void Attack1();

	void SetAnimation();

	void SetState(State state);

private:
	Transform* root;
	CapsuleCollider* bodyCollider;
	SphereCollider* atkCollider[2];


	float moveSpeed = 8.0f;

};