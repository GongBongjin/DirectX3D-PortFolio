#include "Framework.h"

Revenant::Revenant() : ModelAnimator("Revenant")
{
    GetMesh(0)->SetMaterial(AddMaterial("Body"));
    GetMesh(1)->SetMaterial(AddMaterial("Arms"));
    GetMesh(2)->SetMaterial(AddMaterial("Jacket"));
    GetMesh(3)->SetMaterial(AddMaterial("Gun"));
    GetMesh(4)->SetMaterial(AddMaterial("Darkness"));
    GetMesh(7)->SetMaterial(AddMaterial("Weapon"));

    curHp = 40.0f;

    gun = new Transform();
    gunShotPos = new SphereCollider();
    gunShotPos->SetParent(gun);

    root = new Transform();
    bodyCollider = new CapsuleCollider();
    bodyCollider->SetTag("Revenant_Body");
    bodyCollider->SetParent(root);
    bodyCollider->Load();
    
    testUI = false;
    ClientToScreen(hWnd, &clientCenterPos);
    
    crossHair = new Quad(L"Textures/UI/cursor.png");
    crossHair->Pos() = { CENTER_X, CENTER_Y, 0 };
    crossHair->UpdateWorld();
    playerUI = new PlayerUI();
    

    ReadClip("Idle");
    ReadClip("Attack"); 
    ReadClip("Reload");
    ReadClip("MoveForward");


    GetClip(ATTACK)->SetEvent(bind(&Revenant::Shoot, this), 0.0f);
    GetClip(ATTACK)->SetEvent(bind(&Revenant::Shoot, this), 0.75f);
    GetClip(ATTACK)->SetEvent(bind(&Revenant::SetIdle, this), 1.0f);
    GetClip(RELOAD)->SetEvent(bind(&Revenant::SetIdle, this), 0.70f);
}

Revenant::~Revenant()
{
    delete gun;

    delete gunShotPos;

    delete root;
    
    delete bodyCollider;

    delete crossHair;
    delete playerUI;
}

void Revenant::Update()
{
    if (KEY_DOWN(VK_ESCAPE))
        testUI = !testUI;
    
    IsCollision();
    Control();
    SetAnimation();

    gun->SetWorld(GetTransformByNode(75));
    root->SetWorld(GetTransformByNode(0));

    ModelAnimator::Update();

    gunShotPos->UpdateWorld();
    bodyCollider->UpdateWorld();

    playerUI->GetPlayerInfo(curHp, maxHp, gold);
    playerUI->Update();
}

void Revenant::Render()
{
    ModelAnimator::Render();

    bodyCollider->Render();
}

void Revenant::PostRender()
{
    crossHair->Render();

    playerUI->PostRender();
}

void Revenant::GUIRender()
{
    Model::GUIRender();
    //gun->GUIRender();
    //bodyCollider->GUIRender();
    playerUI->GUIRender();
}

void Revenant::Control()
{
    Rotate();
    Move();
    Attack();
    Reload();
}

void Revenant::Move()
{
    //if (curState == ATTACK)
    //{
    //    velocity.x = 0;
    //    velocity.z = 0;
    //    return;
    //}

    bool isMoveZ = false;
    bool isMoveX = false;

    if (KEY_PRESS('W'))
    {
        velocity.z -= DELTA;
        isMoveZ = true;
    }
    if (KEY_PRESS('S'))
    {
        velocity.z += DELTA;
        isMoveZ = true;
    }
    if (KEY_PRESS('A'))
    {
        velocity.x += DELTA;
        isMoveX = true;
    }
    if (KEY_PRESS('D'))
    {
        velocity.x -= DELTA;
        isMoveX = true;
    }

    if (velocity.Length() > 1.0f)
        velocity.Normalize();

    if (!isMoveX)
        velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);
    
    if (!isMoveZ)
        velocity.z = Lerp(velocity.z, 0, deceleration * DELTA);

    Matrix rotY = XMMatrixRotationY(Rot().y);
    Vector3 direction = XMVector3TransformCoord(velocity, rotY);

    //Pos().y = terrain->GetHeight(this->Pos(), nullptr);
    Pos().y = 0;
    Pos() -= direction * moveSpeed * DELTA;
}

void Revenant::Rotate()
{
    Vector3 delta;
    //다시 정상적인 상태로 돌아왔을때 마우스위치변화에 따른 로테이션값 변화를 적용해야함.

    if (testUI)
    {
        delta = mousePos - Vector3(CENTER_X, CENTER_Y);
        SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    }
    else
    {
        delta = Vector3::Zero();
    }

    Rot().y += delta.x * rotSpeed * DELTA;
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
}

void Revenant::Attack()
{
    if (!testUI) return;
    if (curState == ATTACK) return;
    if (curState == RELOAD) return;

    if (KEY_DOWN(VK_LBUTTON))
    {
        if (shootCount >= maxShootCount)
        {
            SetState(RELOAD);
            shootCount = 0;
            return;
        }

        SetState(ATTACK);

        Ray ray = CAM->ScreenPointToRay(mousePos);
        isTarget = EnemyManager::Get()->IsCollision(ray, targetPos);
        //추가해야할 내용 - 타깃과의 충돌이 아니고 허공에 쏠시, 터레인과의 충돌 구현
    }
}

void Revenant::Reload()
{
    if (KEY_DOWN(VK_RBUTTON))
    {
        SetState(RELOAD);
        shootCount = 0;
    }
}

void Revenant::SetAnimation()
{
    if (curState == ATTACK) return;
    if (curState == RELOAD) return;

    if (velocity.z > 0.1f)
        SetState(MOVE_FORWARD);
    else if (velocity.z < -0.1f)
        SetState(MOVE_FORWARD);
    else if (velocity.x > 0.1f)
        SetState(MOVE_FORWARD);
    else if (velocity.x < -0.1f)
        SetState(MOVE_FORWARD);
    else
        SetState(IDLE);
}

void Revenant::SetState(State state)
{
    if (curState == state) return;

    curState = state;
    PlayClip(state);
}

void Revenant::Shoot()
{
    Vector3 dir = CAM->Forward();

    if (isTarget)
        dir = targetPos - gunShotPos->GlobalPos();

    shootCount++;

    if(shootCount <= maxShootCount)
    {
        BulletManager::Get()->Shoot(gunShotPos->GlobalPos(), dir.GetNormalized());
    }
}

void Revenant::IsCollision()
{
    for(BoxCollider* buildingCollider : buildingColliders)
    {
        if (bodyCollider->IsCollision(buildingCollider))
        {
            Vector3 direction = Pos() - buildingCollider->GlobalPos();
            
            Pos() += direction.GetNormalized();
        }
    }
}

void Revenant::SetIdle()
{
    SetState(IDLE);
}
