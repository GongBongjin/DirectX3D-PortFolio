#pragma once

class MainScene : public Scene
{
public:
    MainScene();
    ~MainScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    virtual void Start() override;
    virtual void End() override;

private:
    Skybox* skybox;

    Terrain* terrain;

    Revenant* revenant;

};