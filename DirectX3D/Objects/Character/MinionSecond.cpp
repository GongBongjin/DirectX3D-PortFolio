#include "Framework.h"

MinionSecond::MinionSecond(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	: Enemy(transform, instancing, index)
{
	root = new Transform();

	collider = new CapsuleCollider();
	collider->SetTag("Secondbody_C");
	collider->SetParent(root);
	collider->Pos() = { 0.0f, 66.0f, 0.0f };
	collider->Scale() = { 30.0f, 25.0f, 30.0f };

	arms = new Transform();

	weaponCollider = new BoxCollider();
	weaponCollider->SetTag("Second_weapon");
	weaponCollider->SetParent(arms);
	weaponCollider->Load();
	weaponCollider->SetActive(false);

	speed = 9.0f;
	dmg = 15.0f;
}

MinionSecond::~MinionSecond()
{
	delete root;

	delete collider;

	delete arms;

	delete weaponCollider;
}

void MinionSecond::Update()
{
	if (!transform->Active()) return;

	root->SetWorld(instancing->GetTransformByNode(index, 0));

	arms->SetWorld(instancing->GetTransformByNode(index, 38));

	Enemy::Update();
}

void MinionSecond::Render()
{
	Enemy::Render();
}

void MinionSecond::PostRender()
{
	Enemy::PostRender();
}

void MinionSecond::GUIRender()
{
	collider->GUIRender();

	weaponCollider->GUIRender();
}
