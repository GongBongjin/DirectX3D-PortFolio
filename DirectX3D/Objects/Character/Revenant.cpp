#include "Framework.h"

Revenant::Revenant() : ModelAnimator("Revenant")
{
    GetMesh(0)->SetMaterial(AddMaterial("Body"));
    GetMesh(1)->SetMaterial(AddMaterial("Arms"));
    GetMesh(2)->SetMaterial(AddMaterial("Jacket"));
    GetMesh(3)->SetMaterial(AddMaterial("Gun"));
    GetMesh(4)->SetMaterial(AddMaterial("Darkness"));
    GetMesh(7)->SetMaterial(AddMaterial("Weapon"));

    gun = new Transform();
    gunShotPos = new SphereCollider();
    gunShotPos->SetParent(gun);
    
    ClientToScreen(hWnd, &clientCenterPos);
    
    crossHair = new Quad(L"Textures/UI/cursor.png");
    crossHair->Pos() = { CENTER_X, CENTER_Y, 0 };
    crossHair->UpdateWorld();

    ReadClip("Idle");
    ReadClip("Attack");
    ReadClip("MoveForward");

    GetClip(ATTACK)->SetEvent(bind(&Revenant::Shoot, this), 0.0f);
    GetClip(ATTACK)->SetEvent(bind(&Revenant::Shoot, this), 0.75f);
    GetClip(ATTACK)->SetEvent(bind(&Revenant::EndShoot, this), 1.0f);
}

Revenant::~Revenant()
{
    delete gun;

    delete crossHair;

    delete gunShotPos;
}

void Revenant::Update()
{
    Control();
    SetAnimation();

    gun->SetWorld(GetTransformByNode(75));

    ModelAnimator::Update();

    gunShotPos->UpdateWorld();
}

void Revenant::Render()
{
    ModelAnimator::Render();
}

void Revenant::PostRender()
{
    crossHair->Render();
}

void Revenant::GUIRender()
{
    Model::GUIRender();
    gun->GUIRender();
}

void Revenant::Control()
{
    Rotate();
    Move();
    Attack();
}

void Revenant::Move()
{
    if (curState == ATTACK)
    {
        velocity.x = 0;
        velocity.z = 0;
        return;
    }

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
    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    Rot().y += delta.x * rotSpeed * DELTA;
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
}

void Revenant::Attack()
{
    if (curState == ATTACK) return;

    if (KEY_DOWN(VK_LBUTTON))
    {
        SetState(ATTACK);

        Ray ray = CAM->ScreenPointToRay(mousePos);
        isTarget = EnemyManager::Get()->IsCollision(ray, targetPos);
        //추가해야할 내용 - 타깃과의 충돌이 아니고 허공에 쏠시, 터레인과의 충돌 구현
    }
}

void Revenant::SetAnimation()
{
    if (curState == ATTACK) return;

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

    BulletManager::Get()->Shoot(gunShotPos->GlobalPos(), dir.GetNormalized());
}

void Revenant::EndShoot()
{
    SetState(IDLE);
}
