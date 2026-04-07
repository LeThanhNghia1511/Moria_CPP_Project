#ifndef SPRITE_H
#define SPRITE_H

#include <d3dx9.h>
#include <string>
#include "Texture.h"
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
	bool Initialize(LPDIRECT3DDEVICE9 device, std::wstring file);
	bool IsInitialized();
	virtual void Draw(LPD3DXSPRITE handler, D3DXVECTOR3 position);
	Texture* GetTexture() { return _texture; }	
private:
	Texture* _texture;
	LPD3DXSPRITE _sprite;

	// Atributes
	D3DCOLOR _color;
	bool _initialized;
};


#endif // SPRITE_H