#ifndef GAMEPLAYOBJECT_H
#define GAMEPLAYOBJECT_H
#define _USE_MATH_DEFINES 
#include <cmath>

#include "Sprite.h"
#include <string>

enum class ObjectStatus {Active, Dying, Dead};

class GameObject
{
public:
	// Constructor and Destructor
	GameObject(float x, float y, float rotation, float speed, float maxSpeed);
	~GameObject();

	virtual bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	virtual void HandleInput();
	virtual void Update(float gameTime);
	virtual void Draw(float gameTime);

	ObjectStatus GetStatus() const;

	void SetSpeed(float speed);
protected:
	// Informational data
	std::string _name;
	std::string _description;

	// Physics data
	D3DXVECTOR3 _position;
	D3DXVECTOR3 _velocity;
	float _rotation;
	float _speed;
private:
	ObjectStatus status;
	Sprite* sprite;

	float _maxSpeed;
};

#endif // GAMEPLAYOBJECT_H

