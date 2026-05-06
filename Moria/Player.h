#pragma once
#include "AnimationController.h"
#include "Texture.h"
#include "GameObject.h"

class Player : public GameObject
{
private:
	// Player animation
	AnimationController* animController;

	float _moveX;
	float _moveY;
	float _speed;
	float _isFacingRight;
	
public:
	Collider* collider;

	Player();
	Player(float x, float y, float z);
	~Player();

	bool Initialize(std::wstring path, int width, int height);
	void Update() override;
	void Render(LPD3DXSPRITE handler);

	// Functions
	void HandleInput();	
	void HandleMovement();
	void HandleAnimations();
	void Flip();
};

