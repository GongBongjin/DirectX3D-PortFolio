#include "Framework.h"

MinionFirst::MinionFirst(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	:Enemy(transform, instancing, index)
{
	root = new Transform();

	collider = new CapsuleCollider();
	collider->SetTag("FirstBody_C");
	collider->SetParent(root);
	collider->Pos() = { 0.0f, 66.0f, 0.0f };
	collider->Scale() = { 30.0f, 25.0f, 30.0f };

	arms = new Transform();

	weaponCollider = new BoxCollider();
	weaponCollider->SetTag("First_weapon");
	weaponCollider->SetParent(arms);
	weaponCollider->Load();
	weaponCollider->SetActive(false);

	speed = 9.0f;
	dmg = 10.0f;
}

MinionFirst::~MinionFirst()
{
	delete root;

	delete collider;

	delete arms;

	delete weaponCollider;
}

void MinionFirst::Update()
{
	if (!transform->Active()) return;

	barPos = transform->Pos() + Vector3(0, 12.0f, 0);

	root->SetWorld(instancing->GetTransformByNode(index, 0));

	arms->SetWorld(instancing->GetTransformByNode(index, 38));

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

	weaponCollider->GUIRender();
}
