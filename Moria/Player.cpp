#include "Player.h"

Player::Player() : GameObject()
{
	_speed = 100;
	_moveX = 0;
	_moveY = 0;
	_isFacingRight = true;
	sprite = nullptr;
	animController = nullptr;
}

Player::Player(float x, float y, float z) : GameObject(x, y, z)
{
	_speed = 100;
	_moveX = 0;
	_moveY = 0;
	
	_isFacingRight = true;
	sprite = nullptr;
	animController = nullptr;
}

Player::~Player()
{
	if (animController)
	{
		delete animController;
		animController = nullptr;
	}
}


bool Player::Initialize(std::wstring path, int width, int height)
{
	if (!GameObject::Initialize(path, width, height))
		return false;

	if (sprite != nullptr)
	{
		animController = new AnimationController(sprite->GetTexture(), 48, 48);
		animController->AddClip(0, 4, 0.1f, "Idle");
		animController->AddClip(1, 4, 0.1f, "Walk");
	}

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
		D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0);
		animController->Play(spriteHandler, pos);
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
	if (_moveX < 0 && _isFacingRight) // ->Facing left
	{
		_isFacingRight = false;
		this->transform->scale.x *= -1; // Flip horizontally
	}

	else if (_moveX > 0 && !_isFacingRight) // ->Facing right
	{
		_isFacingRight = true;
		this->transform->scale.x *= -1; // Normal scale
	}
}