#include "Collider.h"
#include "GameObject.h" // Include để xài owner->transform
#include <cmath>

Collider::Collider(GameObject* owner, float w, float h, float ox, float oy, bool trigger)
{
    this->owner = owner;
    this->width = w;
    this->height = h;
    this->offsetX = ox;
    this->offsetY = oy;
    this->isTrigger = trigger;
}

Box Collider::GetBounds()
{
    Box b;
    // Tự động scale khung va chạm theo Scale của Transform
    float currentScaleX = std::abs(owner->transform->scale.x);
    float currentScaleY = std::abs(owner->transform->scale.y);

    b.width = width * currentScaleX;
    b.height = height * currentScaleY;
    b.x = owner->transform->position.x + (offsetX * currentScaleX);
    b.y = owner->transform->position.y + (offsetY * currentScaleY);

    return b;
}