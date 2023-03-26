#pragma once

class MinionSuper : public Enemy
{
public:
	MinionSuper(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
	~MinionSuper();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;
};