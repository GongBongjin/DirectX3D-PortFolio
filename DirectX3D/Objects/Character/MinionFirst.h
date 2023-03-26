#pragma once

class MinionFirst : public Enemy
{
public:
	MinionFirst(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
	~MinionFirst();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;
};