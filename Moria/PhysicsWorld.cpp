#include "PhysicsWorld.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include <cmath>

PhysicsWorld* PhysicsWorld::instance = nullptr;

PhysicsWorld* PhysicsWorld::GetInstance() {
    if (instance == nullptr) instance = new PhysicsWorld();
    return instance;
}

PhysicsWorld::PhysicsWorld() {
    globalGravity = 1000.0f; // Setup trọng lực mặc định (trục Y hướng xuống)
}

void PhysicsWorld::AddCollider(Collider* col) {
    colliders.push_back(col);
}

void PhysicsWorld::RemoveCollider(Collider* col) {
    // Thuật toán xóa collider khỏi vector
    for (auto it = colliders.begin(); it != colliders.end(); ++it) {
        if (*it == col) {
            colliders.erase(it);
            break;
        }
    }
}

bool PhysicsWorld::CheckAABB(Box b1, Box b2) {
    return (b1.x < b2.x + b2.width &&
        b1.x + b1.width > b2.x &&
        b1.y < b2.y + b2.height &&
        b1.y + b1.height > b2.y);
}

// BƯỚC QUAN TRỌNG: XỬ LÝ ĐẨY NHAU CÓ KHỐI LƯỢNG
void PhysicsWorld::ResolveCollision(Collider* colA, Collider* colB)
{
    // Lấy Rigidbody của 2 thằng ra (nếu không có Rigidbody thì coi như vật tĩnh invMass = 0)
    Rigidbody* rbA = colA->owner->rigidbody;
    Rigidbody* rbB = colB->owner->rigidbody;

    float invMassA = (rbA != nullptr) ? rbA->invMass : 0.0f;
    float invMassB = (rbB != nullptr) ? rbB->invMass : 0.0f;

    float sumInvMass = invMassA + invMassB;
    if (sumInvMass == 0.0f) return; // Cả 2 đều đứng im thì dẹp, không đẩy gì hết

    Box bA = colA->GetBounds();
    Box bB = colB->GetBounds();

    // Tính tâm
    float cAx = bA.x + bA.width / 2.0f;
    float cAy = bA.y + bA.height / 2.0f;
    float cBx = bB.x + bB.width / 2.0f;
    float cBy = bB.y + bB.height / 2.0f;

    float distX = cAx - cBx;
    float distY = cAy - cBy;

    float minX = bA.width / 2.0f + bB.width / 2.0f;
    float minY = bA.height / 2.0f + bB.height / 2.0f;

    float overlapX = minX - std::abs(distX);
    float overlapY = minY - std::abs(distY);

    if (overlapX > 0 && overlapY > 0)
    {
        // Trục X lún ít hơn -> Đẩy theo trục X
        if (overlapX < overlapY)
        {
            float pushAmountA = overlapX * (invMassA / sumInvMass);
            float pushAmountB = overlapX * (invMassB / sumInvMass);

            if (distX > 0) { // A bên phải B
                colA->owner->transform->position.x += pushAmountA;
                colB->owner->transform->position.x -= pushAmountB;
            }
            else {         // A bên trái B
                colA->owner->transform->position.x -= pushAmountA;
                colB->owner->transform->position.x += pushAmountB;
            }

            // Triệt tiêu vận tốc X để không bị trôi
            if (rbA) rbA->velocityX = 0;
            if (rbB) rbB->velocityX = 0;
        }
        // Trục Y lún ít hơn -> Đẩy theo trục Y
        else
        {
            float pushAmountA = overlapY * (invMassA / sumInvMass);
            float pushAmountB = overlapY * (invMassB / sumInvMass);

            if (distY > 0) { // A nằm dưới B
                colA->owner->transform->position.y += pushAmountA;
                colB->owner->transform->position.y -= pushAmountB;
            }
            else {         // A nằm trên B
                colA->owner->transform->position.y -= pushAmountA;
                colB->owner->transform->position.y += pushAmountB;
            }

            // Triệt tiêu vận tốc Y để đứng im trên mặt đất
            if (rbA) rbA->velocityY = 0;
            if (rbB) rbB->velocityY = 0;
        }
    }
}

// HÀM CHÍNH GỌI MỖI FRAME
void PhysicsWorld::Step(float dt)
{
    // BƯỚC 1: CẬP NHẬT CHUYỂN ĐỘNG & TRỌNG LỰC CHO TẤT CẢ
    for (int i = 0; i < colliders.size(); i++) {
        Rigidbody* rb = colliders[i]->owner->rigidbody;
        if (rb != nullptr && rb->invMass > 0.0f) { // Chuyển động được
            // Kéo trọng lực
            rb->velocityY += globalGravity * rb->gravityScale * dt;

            // Dời tọa độ
            colliders[i]->owner->transform->position.x += rb->velocityX * dt;
            colliders[i]->owner->transform->position.y += rb->velocityY * dt;
        }
    }



    // BƯỚC 2: KIỂM TRA VA CHẠM (Thuật toán Brute Force cho đơn giản)
    for (int i = 0; i < colliders.size(); i++) {
        for (int j = i + 1; j < colliders.size(); j++) {
            Collider* colA = colliders[i];
            Collider* colB = colliders[j];

            if (CheckAABB(colA->GetBounds(), colB->GetBounds())) {
                if (colA->isTrigger || colB->isTrigger) {
                    // CÓ TRIGGER: Chỉ gọi sự kiện, KHÔNG đẩy (M có thể code thêm hàm OnTriggerEnter sau)
                }
                else {
                    // KHÔNG TRIGGER: Dội mẹ nó ra!
                    ResolveCollision(colA, colB);
                }
            }
        }
    }
}