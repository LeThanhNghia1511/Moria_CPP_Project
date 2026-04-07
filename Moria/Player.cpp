#include "Player.h"

Player::Player()
{
	_speed = 50;
}

Player::Player(float x, float y, float z) : GameObject()
{
	_speed = 70;
	this->transform->position = D3DXVECTOR3(x, y, z);
	this->transform->scale = D3DXVECTOR3(3.0f, 3.0f, 3.0f); // Hiện hình!

	sprite = nullptr;
}

Player::~Player()
{

}


bool Player::Initialize(std::wstring path, int width, int height)
{
	GameObject::Initialize(GraphicsDevice::GetInstance()->device, path, width, height);

	animController = new AnimationController(sprite->GetTexture(), 64, 86);
	animController->AddClip(0, 4, 0.1f, "Idle");
	animController->AddClip(1, 4, 0.1f, "Walk");

	return true;
}

void Player::Update()
{
	HandleInput();
	HandleMovement();
	HandleAnimations();
}

void Player::Render(LPD3DXSPRITE spriteHandler)
{
	if (animController)
	{
		D3DXVECTOR3 testPos(0, 0, 0);
		animController->Play(spriteHandler, testPos);
	}
}

void Player::HandleInput()
{
	D3DXVECTOR3 movement(0, 0, 0);

	// Get key input
	_moveY = Input::GetInstance()->GetAxis("Vertical");
	_moveX = Input::GetInstance()->GetAxis("Horizontal");
	movement.x += _moveX;
	movement.y += _moveY;

	if (movement.x != 0 || movement.y != 0) // Is moving
	{
		float angle = atan2(movement.y, movement.x);

		_velocity.x = _speed * cos(angle);
		_velocity.y = _speed * sin(angle);
	}
	else
	{
		_velocity.x = 0;
		_velocity.y = 0;
	}
}

void Player::HandleMovement()
{
	transform->position.x += _velocity.x * Time::GetDeltaTime();
	transform->position.y += _velocity.y * Time::GetDeltaTime();

	if (_moveX != 0)
		Flip();
}

void Player::HandleAnimations()
{
	// Update animation theo velocity
	if (_velocity.x != 0 || _velocity.y != 0)
	{
		animController->ChangeClip("Walk");
	}
	else
	{
		animController->ChangeClip("Idle");
	}
}

void Player::Flip()
{
	if (_moveX < 0) // Facing left
	{
		this->transform->scale.x = -3; // Flip horizontally
	}

	else if (_moveX > 0) // Facing right
	{
		this->transform->scale.x = 3; // Normal scale
	}
}