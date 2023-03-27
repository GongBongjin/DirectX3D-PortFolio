#pragma once

class Enemy
{
protected:
    enum State
    {
        IDLE,
        WALK,
        ATTACK,
        HIT,
        DYING
    }curState = IDLE;

public:
    Enemy(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
    ~Enemy();

    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void PostRender() = 0;
    virtual void GUIRender() = 0;

    void Spawn(Vector3 pos);
    void Hitted();

    CapsuleCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

    void SetTarget(Transform* target) { this->target = target; }

    void SetState(State state);

protected:
    Vector3 pos;
    Transform* transform;
    CapsuleCollider* collider;

    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    Transform* root;
    ProgressBar* hpBar;
    Transform* target;

    float speed = 50.0f;
    float maxHp = 100.0f;
    float curHp = 100.0f;

    Vector3 velocity;
    Vector3 barPos;

    UINT index;

    vector<map<float, Event>> totalEvent;
    vector<map<float, Event>::iterator> eventIters;
};