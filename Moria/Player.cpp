#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}


bool Player::Initialize(std::wstring path)
{
	return GameObject::Initialize(GraphicsDevice::GetInstance()->device, path, 100, 100);
}

void Player::Update(float deltaTime)
{
   
}

void Player::Draw(float gameTime)
{

}