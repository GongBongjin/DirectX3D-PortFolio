#pragma once

class Revenant : public ModelAnimator
{
private:
    enum State
    {
        IDLE,
        ATTACK,
        RELOAD,
        HITTED,
        DYING,
        MOVE_FORWARD
    }curState = IDLE;

    enum ItemKey
    {
        HP=101,
        MP,
        BOW,
        HELMETS
    }itemKey;

    const float POSION_TIME = 10.0f;

public:
    Revenant();
    ~Revenant();

    void Update();
    void Render();
    void PreRender();
    void PostRender();
    void GUIRender();

    void GetTerrain(Terrain* terrain) { this->terrain = terrain; }
    void GetBuildingCollider(vector<BoxCollider*> buildingColliders) { this->buildingColliders = buildingColliders; }

    float GetDmg() { return dmg; }
    void GetGold(UINT gold);
    void Hitted(float targetdmg);
    
    CapsuleCollider* GetBodyCollider() { return bodyCollider; }

private:
    void Control();
    void Move();
    void Rotate();
    void Attack();
    void Reload();
    void Dying();

    void SetAnimation();
    void SetState(State state);

    void Shoot();
    void IsCollision();

    void UseItem();

//Event Function
private:
    void SetIdle();
    void SetDead();
    void SetReloadParticle();


private:
    Transform* root;
    Transform* gun;
    SphereCollider* gunShotPos;
    CapsuleCollider* bodyCollider;
    PlayerUI* playerUI;

    float dmg= 10.0f;
    float defenceValue = 20.0f;

    float curHp;
    float maxHp = 100.0f;
    float hpRecoveryValue = 1.0f;

    float curMp;
    float maxMp = 100.0f;
    float mpRecoveryValue = 1.0f;

    bool isTakeHpPosion = false;
    bool isTakeMpPosion = false;

    float hpPosionTime = 0.0f;
    float mpPosionTime = 0.0f;

    float moveSpeed = 20.0f;
    float rotSpeed = 1.0f;
    float deceleration = 3.0f;

    UINT shootCount = 0;
    const UINT maxShootCount = 4;

    vector<Item*> invenItems;

    Vector3 velocity;
    Vector3 targetPos;

    bool isTarget;

    POINT clientCenterPos = { WIN_WIDTH >> 1, WIN_HEIGHT >> 1 };

    Quad* crossHair;
    Terrain* terrain;

    vector<BoxCollider*> buildingColliders;
};