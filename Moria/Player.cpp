#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}


bool Player::Initialize(std::wstring path, int width, int height)
{
	GameObject::Initialize(GraphicsDevice::GetInstance()->device, path, width, height);

	animController = new AnimationController(sprite->GetTexture(), 240, 240, 0.2f);
	animController->AddClip(0, 4, 1.3f, "Idle");
	animController->AddClip(1, 4, 1.0f, "Walk");

	// Khởi tạo các thông số cho Player
	_speed = 200.0f;
	_maxSpeed = 500.0f;

	return true;
}

void Player::Update(float gameTime)
{
	// Xu li input cua nguoi choi
	HandleInput();

	// Xu li di chuyen cua gameobj
	GameObject::Update(gameTime);

	// Update animtion theo velocity
	if (_velocity.x != 0 || _velocity.y != 0)
	{
		animController->ChangeClip("Walk");
	}
	else
	{
		animController->ChangeClip("Idle");
	}
}

void Player::Draw(float gameTime)
{
	if (animController)
	{
		animController->Play(_position);
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

void Player::Flip()
{
	if (_moveX < 0) // Facing left
	{

	}
}