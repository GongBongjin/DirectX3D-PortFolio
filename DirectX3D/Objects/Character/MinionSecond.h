#pragma once

class MinionSecond : public Enemy
{
public:
	MinionSecond(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
	~MinionSecond();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;
};