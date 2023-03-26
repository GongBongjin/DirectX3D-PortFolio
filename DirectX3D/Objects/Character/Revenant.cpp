#include "Framework.h"

Revenant::Revenant() : ModelAnimator("Revenant")
{
    ClientToScreen(hWnd, &clientCenterPos);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    crossHair = new Quad(L"Textures/UI/cursor.png");
    crossHair->Pos() = { CENTER_X, CENTER_Y, 0 };
    crossHair->UpdateWorld();

    ReadClip("Idle");
    ReadClip("Attack");
    ReadClip("MoveForward");

    GetClip(ATTACK)->SetEvent(bind(&Revenant::EndShoot, this), 1.0f);
}

Revenant::~Revenant()
{
    //delete crossHair;
}

void Revenant::Update()
{
    Control();
    SetAnimation();

    ModelAnimator::Update();
}

void Revenant::Render()
{
    ModelAnimator::Render();
}

void Revenant::PostRender()
{
    //crossHair->Render();
}

void Revenant::GUIRender()
{
    Model::GUIRender();
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
        //isTarget = RobotManager::Get()->IsCollision(ray, targetPos);
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

void Revenant::EndShoot()
{
    SetState(IDLE);
}
