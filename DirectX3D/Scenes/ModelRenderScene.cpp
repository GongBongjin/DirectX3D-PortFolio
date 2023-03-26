#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
    model = new Model("Third");
    //model->GetMesh(1)->SetMaterial(model->AddMaterial());
    //model->GetMesh(2)->SetMaterial(model->AddMaterial());
    //model->GetMesh(3)->SetMaterial(model->AddMaterial());
    //model->GetMesh(4)->SetMaterial(model->AddMaterial());    
}

ModelRenderScene::~ModelRenderScene()
{
    delete model;
}

void ModelRenderScene::Update()
{
    model->UpdateWorld();
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
    model->Render();
}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
    model->GUIRender();
}
