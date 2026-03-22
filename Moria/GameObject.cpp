#include "GameObject.h"

GameObject::GameObject(float x, float y, float rotation, float speed, float maxSpeed)
{
	float twoPi = (float)(M_PI * 2);
	_position.x = x;
	_position.y = y;
	_position.z = 0;

	if (rotation > twoPi) rotation = twoPi;
	if (rotation < 0) rotation = 0;

	if (speed > maxSpeed) speed = maxSpeed;
	if (speed < 0) speed = 0;

	this->_rotation = rotation;
	this->_maxSpeed = maxSpeed;

	SetSpeed(speed);
}

bool GameObject::Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
{
	status = ObjectStatus::Active;

	if (!sprite)
	{
		sprite = new Sprite();
		if (!sprite->Initialize(device, file, width, height))
		{
			return false;
		}
	}
	return true;
}

void GameObject::HandleInput()
{
	D3DXVECTOR3 movement(0, 0, 0);

	// Get key input
	if (GetAsyncKeyState(VK_UP))
	{
		movement.y -= 1;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		movement.y += 1;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		movement.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		movement.x += 1;
	}

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

void GameObject::Update(float gameTime)
{
	if (status == ObjectStatus::Active)
	{
		_position.x += _velocity.x * gameTime;
		_position.y += _velocity.y * gameTime;
		_position.z = 0;
	}
}

void GameObject::Draw(float gameTime)
{
	if (sprite)
		sprite->Draw(gameTime, _position);
}

ObjectStatus GameObject::GetStatus() const
{
	return status;
}

void GameObject::SetSpeed(float speed)
{
	if (speed >= 0 && speed <= _maxSpeed)
	{
		this->_speed = speed;
		_velocity.x = cos(_rotation) * speed;
		_velocity.y = sin(_rotation) * speed;
		_velocity.z = 0;
	}
}

GameObject::~GameObject()
{
	if (sprite)
	{
		delete sprite;
		sprite = 0;
	}
}