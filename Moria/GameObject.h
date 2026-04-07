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

enum class ObjectStatus {Active, Dying, Dead};

class GameObject
{
public:
	// Constructor and Destructor
	GameObject();
	GameObject(float x, float y);
	~GameObject();

	virtual bool Initialize(LPDIRECT3DDEVICE9 device, std::wstring file, int width, int height);
	virtual void Update();
	void Draw();
	virtual void Render(LPD3DXSPRITE spriteHandler) = 0;

	//ObjectStatus GetStatus() const;
protected:
	Sprite* sprite;
	LPD3DXSPRITE spriteHandler;
	// Informational data
	std::string _name;
	std::string _description;

	// Physics data
	Transform* transform;
	D3DXVECTOR3 _velocity;
};

#endif // GAMEPLAYOBJECT_H

