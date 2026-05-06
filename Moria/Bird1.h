#pragma once
#include "GameObject.h"
#include "AnimationController.h"

class Bird1 : public GameObject
{
private:
	AnimationController* animController;

	float speed;
	
public:
	Collider* collider;

	Bird1();
	Bird1(float x, float y, float z);
	~Bird1();

	bool Initialize(std::wstring path, int width, int height);
	void Update() override;
	void Render(LPD3DXSPRITE spriteHandler);
};

