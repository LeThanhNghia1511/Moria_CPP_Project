#pragma once
#include "Animation.h"
#include "Texture.h"
#include "GameObject.h"
#include "Input.h"

class Player : public GameObject
{
private:
	// Player states
	Texture* texture;
	Animation* animIdle;
	Animation* animWalk;
	Animation* animJump;
	Animation* currentAnim;

	float _moveX;
	float _moveY;
	
public:
	// Functions
	Player();
	~Player();

	bool Initialize(std::wstring path, int width, int height);
	void Update(float gameTime);
	void Draw(float gameTime);
	void HandleInput();
	void Flip();
};

