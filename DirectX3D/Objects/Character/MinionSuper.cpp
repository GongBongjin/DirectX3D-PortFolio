#include "Framework.h"

MinionSuper::MinionSuper(Transform* transform, ModelAnimatorInstancing* instancing, UINT index) 
	: Enemy(transform, instancing, index)
{
	root = new Transform();

	collider = new CapsuleCollider();
	collider->SetTag("SuperBody_C");
	collider->SetParent(root);
	collider->Pos() = { 0.0f, 110.0f, 15.0f };
	collider->Scale() = { 60.0f, 50.0f, 60.0f };

	arms = new Transform();
	
	weaponCollider = new BoxCollider();
	weaponCollider->SetTag("Super_weapon1");
	weaponCollider->SetParent(arms);
	weaponCollider->Load();
	weaponCollider->SetActive(false);

	speed = 8.0f;
	dmg = 20.0f;
}

MinionSuper::~MinionSuper()
{
	delete root;

	delete collider;

	delete arms;

	delete weaponCollider;
}

void MinionSuper::Update()
{
	if (!transform->Active()) return;

	root->SetWorld(instancing->GetTransformByNode(index, 0));
	arms->SetWorld(instancing->GetTransformByNode(index, 18));

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

	weaponCollider->GUIRender();
}