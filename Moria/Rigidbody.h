#pragma once
class GameObject; // Khai báo trước để tránh lỗi Include chéo

class Rigidbody
{
public:
    GameObject* owner; // Chủ nhân của Component này

    float velocityX, velocityY;
    float mass;         // Khối lượng (m)
    float invMass;      // Nghịch đảo khối lượng (1/m). Tường đứng im thì invMass = 0
    float gravityScale; // Độ ảnh hưởng của trọng lực (0 = bay lơ lửng, 1 = rớt bình thường)

    // Khởi tạo. Mặc định mass = 0 nghĩa là vật thể Tĩnh (Static - Tường, Đất)
    Rigidbody(GameObject* owner, float mass = 0.0f, float gravityScale = 1.0f);

    void AddForce(float forceX, float forceY);
};