#include "Rigidbody.h"

Rigidbody::Rigidbody(GameObject* owner, float mass, float gravityScale)
{
    this->owner = owner;
    this->velocityX = 0.0f;
    this->velocityY = 0.0f;
    this->gravityScale = gravityScale;

    // Xử lý Inverse Mass
    this->mass = mass;
    if (mass <= 0.0f) {
        this->invMass = 0.0f; // Vật thể vô hạn kg (Static)
    }
    else {
        this->invMass = 1.0f / mass; // Vật thể Dynamic (có thể đẩy được)
    }
}

void Rigidbody::AddForce(float forceX, float forceY)
{
    if (invMass == 0.0f) return; // Static thì đéo nhận lực

    // a = F / m  => a = F * invMass
    velocityX += forceX * invMass;
    velocityY += forceY * invMass;
}