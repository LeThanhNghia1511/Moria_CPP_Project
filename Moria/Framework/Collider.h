#pragma once

// Cấu trúc khung Box 
struct Box {
    float x, y, width, height;
};

class GameObject;

class Collider
{
public:
    GameObject* owner;

    float width, height;
    float offsetX, offsetY;
    bool isTrigger; // true = đi xuyên qua được (chỉ bắt sự kiện), false = va chạm cứng

    Collider(GameObject* owner, float w, float h, float ox = 0, float oy = 0, bool trigger = false);

    Box GetBounds();
};