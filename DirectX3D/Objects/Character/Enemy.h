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
    BoxCollider* GetAtkCollider() { return weaponCollider; }
    Transform* GetTransform() { return transform; }
    float GetDmg() { return dmg; }
    float GetHp() { return curHp; }

    void SetTarget(Revenant* target) { this->target = target; }

    void SetState(State state);

    void SetEvent(int clip, Event event, float timeRatio);
    void ExcuteEvent();

    void SetTerrain(Terrain* terrain) { this->terrain = terrain; }
    void SetAStar(AStar* aStar) { this->aStar = aStar; }
    void SetPath();

private:
    void test();
    void Move();
    void Attack();
    void Dead();

    void UpdateHpBar();

public:
    void Hitted();
    void isDead();
    void EndAttack();

//Event Fucntion
private:
    void ComboAttack();
    void SetIdle();
    void EndDyingDC();
    void EndDyingDT();
    void StartAttack();
    

protected:
    float dmg;

    Vector3 pos;
    Transform* transform;
    CapsuleCollider* collider;

    Transform* arms;
    BoxCollider* weaponCollider;

    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    Transform* root;
    ProgressBar* hpBar;
    Revenant* target;

    float speed;
    float curHp = 50.0f;
    float maxHp = 100.0f;

    float attackRange = 10.0f;
    float chaseRange = 40.0f;

    Vector3 barPos;

    Vector3 range;

    Vector3 destPos;
    vector<Vector3> path;

    UINT index;
    vector<map<float, Event>> totalEvent;
    vector<map<float, Event>::iterator> eventIters;

    Terrain* terrain;
    AStar* aStar;
};