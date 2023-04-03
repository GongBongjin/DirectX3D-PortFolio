#pragma once

class Enemy
{
public:
    enum State
    {
        IDLE,
        MOVE,
        ATTACK,
        ATTACK1,
        HITTED,
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

    CapsuleCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

    void SetTarget(Transform* target) { this->target = target; }

    void SetState(State state);

    void SetEvent(int clip, Event event, float timeRatio);
    void ExcuteEvent();

    void SetTerrain(Terrain* terrain) { this->terrain = terrain; }
    void SetAStar(AStar* aStar) { this->aStar = aStar; }
    void SetPath();

private:
    void Move();
    void Attack();
    void Dead();

//Event Fucntion
private:
    void ComboAttack();
    void SetIdle();

public:
    void Hitted();

private:
    void EndDyingDC();
    void EndDyingDT();

protected:
    Vector3 pos;
    Transform* transform;
    CapsuleCollider* collider;

    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    Transform* root;
    ProgressBar* hpBar;
    Transform* target;

    float speed;
    float curHp = 100.0f;
    float maxHp = 100.0f;

    float attackRange = 3.0f;
    float chaseRange = 10.0f;

    Vector3 barPos;
    Vector3 velocity;
    Vector3 direction;
    Vector3 destPos;
    vector<Vector3> path;

    UINT index;
    vector<map<float, Event>> totalEvent;
    vector<map<float, Event>::iterator> eventIters;

    Terrain* terrain;
    AStar* aStar;
};