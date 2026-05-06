#ifndef GAMEPLAYOBJECT_H
#define GAMEPLAYOBJECT_H
#define _USE_MATH_DEFINES 
#include <cmath>

#include "Sprite.h"
#include <string>
#include "Input.h"
#include "AnimationController.h"
#include "Transform.h"
#include "Time.h"
#include "Collider.h"
#include "Rigidbody.h"

enum class ObjectStatus {Active, Dying, Dead};

class GameObject
{
public:
	Transform* transform;
	Rigidbody* rigidbody;
	Collider* collider;

	// Constructor and Destructor
	GameObject();
	GameObject(float x, float y, float z);
	~GameObject();

	virtual bool Initialize(std::wstring file, int width, int height);
	virtual void Update();
	void Draw();
	virtual void Render(LPD3DXSPRITE spriteHandler);

	//ObjectStatus GetStatus() const;
protected:
	Sprite* sprite;
	LPD3DXSPRITE spriteHandler;
	// Informational data
	std::string _name;
	std::string _description;

	// Physics data
	D3DXVECTOR3 _velocity;
};

#endif // GAMEPLAYOBJECT_H

