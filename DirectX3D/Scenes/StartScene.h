#pragma once

class StartScene : public Scene
{
public:
	StartScene();
	~StartScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

	void PushStartButton();

private:
	Quad* backGroundQuad;

	Button* startButton;
};