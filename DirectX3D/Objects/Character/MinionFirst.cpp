#include "Framework.h"

MinionFirst::MinionFirst(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	:Enemy(transform, instancing, index)
{
	root = new Transform();

	collider = new CapsuleCollider();
	collider->SetParent(root);
	collider->Pos() = { 0.0f, 66.0f, 0.0f };
	collider->Scale() = { 30.0f, 25.0f, 30.0f };

	speed = 9.0f;
}

MinionFirst::~MinionFirst()
{
	delete root;

	delete collider;
}

void MinionFirst::Update()
{
	if (!transform->Active()) return;

	root->SetWorld(instancing->GetTransformByNode(index, 0));

	Enemy::Update();
}

void MinionFirst::Render()
{
	Enemy::Render();
}

void MinionFirst::PostRender()
{
	Enemy::PostRender();
}

void MinionFirst::GUIRender()
{
	collider->GUIRender();
}
