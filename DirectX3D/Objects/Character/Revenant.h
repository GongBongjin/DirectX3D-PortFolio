#pragma once

class Revenant : public ModelAnimator
{
private:
    enum State
    {
        IDLE,
        ATTACK,
        RELOAD,
        MOVE_FORWARD
    }curState = IDLE;

public:
    Revenant();
    ~Revenant();

    void Update();
    void Render();
    void PostRender();
    void GUIRender();

    void GetTerrain(Terrain* terrain) { this->terrain = terrain; }
    void GetBuildingCollider(vector<BoxCollider*> buildingColliders) { this->buildingColliders = buildingColliders; }

private:
    void Control();
    void Move();
    void Rotate();
    void Attack();
    void Reload();

    void SetAnimation();

    void SetState(State state);

    void Shoot();

    void IsCollision();
//Event Function
private:
    void SetIdle();


private:
    Transform* root;
    Transform* gun;
    SphereCollider* gunShotPos;
    CapsuleCollider* bodyCollider;
    PlayerUI* playerUI;

    float moveSpeed = 20.0f;
    float rotSpeed = 1.0f;
    float deceleration = 3.0f;
    UINT shootCount = 0;
    const UINT maxShootCount = 4;

    Vector3 velocity;
    Vector3 targetPos;

    bool isTarget;

    POINT clientCenterPos = { WIN_WIDTH >> 1, WIN_HEIGHT >> 1 };

    Quad* crossHair;
    Terrain* terrain;

    vector<BoxCollider*> buildingColliders;
};