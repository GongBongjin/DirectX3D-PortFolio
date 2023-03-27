#pragma once

class Revenant : public ModelAnimator
{
private:
    enum State
    {
        IDLE,
        ATTACK,
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

private:
    void Control();
    void Move();
    void Rotate();
    void Attack();
    void SetAnimation();

    void SetState(State state);

    void Shoot();
//Event Function
private:
    void EndShoot();


private:
    Transform* root;
    CapsuleCollider* bodyCollider;

    float moveSpeed = 10.0f;
    float rotSpeed = 1.0f;
    float deceleration = 3.0f;

    Vector3 velocity;
    Vector3 targetPos;

    bool isTarget;

    POINT clientCenterPos = { WIN_WIDTH >> 1, WIN_HEIGHT >> 1 };

    Quad* crossHair;
    Terrain* terrain;
};