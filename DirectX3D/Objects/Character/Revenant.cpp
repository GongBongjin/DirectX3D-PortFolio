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
    curMp = 80.0f;

    gun = new Transform();
    gunShotPos = new SphereCollider();
    gunShotPos->SetParent(gun);

    root = new Transform();
    bodyCollider = new CapsuleCollider();
    bodyCollider->SetTag("Revenant_Body");
    bodyCollider->SetParent(root);
    bodyCollider->Load();
    
    ClientToScreen(hWnd, &clientCenterPos);
    
    crossHair = new Quad(L"Textures/UI/cursor.png");
    crossHair->Pos() = { CENTER_X, CENTER_Y, 0 };
    crossHair->UpdateWorld();

    playerUI = new PlayerUI(dmg, defenceValue, curHp, maxHp, hpRecoveryValue, curMp, maxMp,mpRecoveryValue, moveSpeed);
       
    ReadClip("Idle");
    ReadClip("Attack"); 
    ReadClip("Reload");
    ReadClip("Hitted");
    ReadClip("Dying");
    ReadClip("MoveForward");

    GetClip(ATTACK)->SetEvent(bind(&Revenant::Shoot, this), 0.0f);
    GetClip(ATTACK)->SetEvent(bind(&Revenant::Shoot, this), 0.75f);
    GetClip(ATTACK)->SetEvent(bind(&Revenant::SetIdle, this), 1.0f);
    GetClip(RELOAD)->SetEvent(bind(&Revenant::SetIdle, this), 0.70f);
    GetClip(HITTED)->SetEvent(bind(&Revenant::SetIdle, this), 0.75f);
    GetClip(DYING)->SetEvent(bind(&Revenant::SetDead, this), 0.9f);
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
    if (!isActive) return;

    if (KEY_DOWN('I'))
        playerUI->GetInven()->isUIOn() != playerUI->GetInven()->isUIOn();
    
    UseItem();
    IsCollision();
    Control();
    SetAnimation();

    gun->SetWorld(GetTransformByNode(75));
    root->SetWorld(GetTransformByNode(0));

    ModelAnimator::Update();

    gunShotPos->UpdateWorld();
    bodyCollider->UpdateWorld();

    playerUI->Update();
}

void Revenant::Render()
{
    if (!isActive) return;

    ModelAnimator::Render();

    bodyCollider->Render();
}

void Revenant::PostRender()
{
    if (!isActive) return;

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

void Revenant::GetGold(UINT gold)
{
    playerUI->GetInven()->GetGold(gold);
}

void Revenant::Hitted(float targetdmg)
{
    if (curState == DYING) return;

    SetState(HITTED);

    curHp -= targetdmg;
}

void Revenant::Control()
{
    Dying();
    Rotate();
    Move();
    Attack();
    Reload();
}

void Revenant::Move()
{
    if (curState == ATTACK || curState == RELOAD)
    {
        velocity.x = 0;
        velocity.z = 0;
        return;
    }

    if (curState == DYING) return;

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
    //�ٽ� �������� ���·� ���ƿ����� ���콺��ġ��ȭ�� ���� �����̼ǰ� ��ȭ�� �����ؾ���.

    if (!playerUI->GetInven()->isUIOn())
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
    if (playerUI->GetInven()->isUIOn()) return;
    if (curState == ATTACK) return;
    if (curState == RELOAD) return;
    if (curState == DYING) return;

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
        //�߰��ؾ��� ���� - Ÿ����� �浹�� �ƴϰ� ����� ���, �ͷ��ΰ��� �浹 ����
    }
}

void Revenant::Reload()
{
    if (playerUI->GetInven()->isUIOn()) return;
    if (curState == DYING) return;

    if (KEY_DOWN(VK_RBUTTON))
    {
        SetState(RELOAD);
        shootCount = 0;
    }
}

void Revenant::Dying()
{
    if (curHp < 1)
    {
        curHp = 0;
        SetState(DYING);
    }
}

void Revenant::SetAnimation()
{
    if (curState == ATTACK) return;
    if (curState == RELOAD) return;
    if (curState == HITTED) return;
    if (curState == DYING) return;

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

void Revenant::UseItem()
{
    if (curState == DYING) return;

    if (!playerUI->GetInven()->GetInvenItemData().empty());
    {
        vector<Item*> tmp = playerUI->GetInven()->GetInvenItemData();
        
        for (int i = 0; i < tmp.size(); i++)
        {
            switch (tmp[i]->GetData().key)
            {
            case HP:
                if (KEY_DOWN('1'))
                {
                    if(tmp[i]->GetCount()>0)
                    {
                        playerUI->GetInven()->UseItem(tmp[i]);
                        if(curHp!=maxHp)
                            hpRecoveryValue = 3.0f;
                        isTakeHpPosion = true;
                    }
                }
                break;
            case MP:
                if (KEY_DOWN('2'))
                {
                    if(tmp[i]->GetCount()>0)
                    {
                        playerUI->GetInven()->UseItem(tmp[i]);
                        mpRecoveryValue = 3.0f;
                        isTakeMpPosion = true;
                    }
                }
                break;
            case BOW:
                if (tmp[i]->GetCount() > 0)
                {
                    dmg = 30.0f;
                    maxMp = 150.0f;
                }
                break;
            case HELMETS:
                if (tmp[i]->GetCount() > 0)
                {
                    defenceValue = 40.0f;
                    maxHp = 200.0f;
                }
                break;
            }
        }    
    }

    if(isTakeHpPosion)
        hpPosionTime += DELTA;

    if(isTakeMpPosion)
        mpPosionTime += DELTA;

    if (hpPosionTime > POSION_TIME)
    {
        hpPosionTime -= POSION_TIME;
        hpRecoveryValue = 1.0f;
        isTakeHpPosion = false;
    }

    if (mpPosionTime > POSION_TIME)
    {
        mpPosionTime -= POSION_TIME;
        mpRecoveryValue = 1.0f;
        isTakeMpPosion = false;
    }

    if (curHp >= maxHp)
    {
        curHp = maxHp;
        hpRecoveryValue = 1.0f;
    }
    else
        curHp += hpRecoveryValue * DELTA;

    if (curMp >= maxMp)
    {
        curMp = maxMp;
        mpRecoveryValue = 1.0f;
    }
    else
        curMp += mpRecoveryValue * DELTA;    
}

void Revenant::SetIdle()
{
    SetState(IDLE);
}

void Revenant::SetDead()
{
    bodyCollider->SetActive(false);

    isActive = false;
}
