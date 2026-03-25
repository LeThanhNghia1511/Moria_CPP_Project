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

	// Tao animation
	Animation* idle = new Animation(0.1f);
	idle->AddFrame(0, 0, 125, 80);   // Frame 1
	idle->AddFrame(125, 0, 125, 80);   // Frame 1
	idle->AddFrame(250, 0, 125, 80);   // Frame 1
	idle->AddFrame(375, 0, 125, 80);   // Frame 1
	sprite->AddAnimation("IDLE", idle);

	Animation* walk = new Animation(0.1f);
	sprite->AddAnimation("WALK", walk);
	walk->AddFrame(0, 80, 125, 80); // Frame 1
	walk->AddFrame(125, 80, 125, 80); // Frame 1
	walk->AddFrame(250, 80, 125, 80); // Frame 1
	walk->AddFrame(375, 80, 125, 80); // Frame 1

	// Set default animation
	sprite->Play("IDLE");

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
		sprite->Play("WALK");
	}
	else
	{
		sprite->Play("IDLE");
	}

	// Cap nhat frame theo thoi gian
	if (sprite)
		sprite->Update(gameTime);
}

void Player::Draw(float gameTime)
{
	GameObject::Draw(gameTime);
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