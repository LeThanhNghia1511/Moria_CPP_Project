#ifndef SPRITE_H
#define SPRITE_H

#include <d3dx9.h>
#include <string>
#include "Texture.h"
#include "Animation.h"
#include <map>

class Sprite
{
public:
	//Attributes
	D3DXVECTOR3 velocity;

	// Constructors and Destructor
	Sprite();
	~Sprite();

	// Functions
	bool Initialize(LPDIRECT3DDEVICE9 device, std::wstring file, int width, int height);
	bool IsInitialized();
	void AddAnimation(std::string name, Animation* anim) {
		_animations[name] = anim;
	}

	void Play(std::string name) {
		if (_animations.count(name))
			_currentAnimation = _animations[name];
	}

	void Update(float dt) {
		if (_currentAnimation) _currentAnimation->Update(dt);
	}
	virtual void Draw(float gameTime, D3DXVECTOR3 position);
private:
	Texture* _texture;
	LPD3DXSPRITE _sprite;
	std::map<std::string, Animation*> _animations;
	Animation* _currentAnimation;


	// Atributes
	D3DCOLOR _color;
	bool _initialized;
};


#endif // SPRITE_H