#include "Framework.h"

MinionSuper::MinionSuper(Transform* transform, ModelAnimatorInstancing* instancing, UINT index) 
	: Enemy(transform, instancing, index)
{
	root = new Transform();

	collider = new CapsuleCollider();
	collider->SetParent(root);
	collider->Pos() = { 0.0f, 110.0f, 15.0f };
	collider->Scale() = { 60.0f, 50.0f, 60.0f };

	speed = 8.0f;
}

MinionSuper::~MinionSuper()
{
	delete root;

	delete collider;
}

void MinionSuper::Update()
{
	if (!transform->Active()) return;

	root->SetWorld(instancing->GetTransformByNode(index, 0));

	Enemy::Update();
}

void MinionSuper::Render()
{
	Enemy::Render();
}

void MinionSuper::PostRender()
{
	Enemy::PostRender();
}

void MinionSuper::GUIRender()
{
	collider->GUIRender();
}