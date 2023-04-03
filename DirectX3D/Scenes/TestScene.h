#pragma once

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	//Building* building;
	Terrain* terrain;
	AStar* aStar;
};