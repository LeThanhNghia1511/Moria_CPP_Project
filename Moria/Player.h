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
	
public:
	// Functions
	Player();
	~Player();

	void Update(float deltaTime);
	void Draw(float gameTime);
	bool Initialize(std::wstring path);
};

