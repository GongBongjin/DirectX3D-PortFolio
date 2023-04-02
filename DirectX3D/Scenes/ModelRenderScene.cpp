#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
    model = new Model("Boss");
    model->Rot().x = XM_PIDIV2;
    model->GetMesh(0)->SetMaterial(model->AddMaterial("Torso"));
    model->GetMesh(1)->SetMaterial(model->AddMaterial("Limbs"));
    //model->GetMesh(2)->SetMaterial(model->AddMaterial("Jacket"));
    //model->GetMesh(3)->SetMaterial(model->AddMaterial("Gun"));
    //model->GetMesh(4)->SetMaterial(model->AddMaterial("Darkness"));
    //model->GetMesh(7)->SetMaterial(model->AddMaterial("Weapon"));
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
    ImGui::SliderInt("MeshNum", &selectMeshNum, 0, model->GetMeshNum());
    if (ImGui::Button("AddMaterial"))
    {
        model->GetMesh(selectMeshNum)->SetMaterial(model->AddMaterial());
    }

    ImGui::SameLine();

    if (ImGui::Button("Save"))
    {
        SaveMaterial();
    }

    model->GUIRender();
}

void ModelRenderScene::SaveMaterial()
{
    string name = model->GetName();
    vector<Material*> materials = model->GetMaterials();

    string savePath = "Models/Materials/" + name + "/";

    CreateFolders(savePath);

    for (Material* material : materials)
    {
        string path = savePath + material->GetName() + ".mat";
        material->Save(path);
    }
}
