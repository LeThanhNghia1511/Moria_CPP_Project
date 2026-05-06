#include "Bird1.h"

Bird1::Bird1()
{
	transform->position = D3DXVECTOR3(0, 0, 0);
	speed = 0;
	animController = nullptr;

}

Bird1::Bird1(float x, float y, float z)
{
	transform->position = D3DXVECTOR3(x, y, z);
	speed = 0;
	animController = nullptr;

}

Bird1::~Bird1()
{
	if (animController)
	{
		delete animController;
		animController = nullptr;
	}
}

bool Bird1::Initialize(std::wstring path, int width, int height)
{
	bool result = GameObject::Initialize(path, width, height);
	if (result == false) return false;

	// Create AnimationController now that sprite (and its texture) is initialized
	if (sprite && sprite->GetTexture())
	{
		animController = new AnimationController(sprite->GetTexture(), 48, 48);
		// Animation
		animController->AddClip(0,3,0.2f, "Idle");
	}

	return true;
}

void Bird1::Update()
{

}

void Bird1::Render(LPD3DXSPRITE spriteHandler)
{
	if (animController)
	{
		animController->Play(spriteHandler, transform->position);
	}
}