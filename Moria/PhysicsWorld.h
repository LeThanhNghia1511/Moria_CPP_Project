#pragma once
#include <vector>
#include "Collider.h"

class PhysicsWorld
{
private:
    static PhysicsWorld* instance;
    std::vector<Collider*> colliders; // Danh sách toàn bộ Collider trong game

    float globalGravity; // Trọng lực tổng của cả thế giới

    // Hàm nội bộ
    bool CheckAABB(Box b1, Box b2);
    void ResolveCollision(Collider* a, Collider* b);

public:
    PhysicsWorld();
    static PhysicsWorld* GetInstance();

    void SetGravity(float g) { globalGravity = g; }

    void AddCollider(Collider* col);
    void RemoveCollider(Collider* col);

    // Chạy vật lý mỗi frame
    void Step(float dt);
};