#ifndef SPRITE_H
#define SPRITE_H

#include <d3dx9.h>
#include <string>

class Sprite
{
public:
	//Attributes
	D3DXVECTOR3 velocity;

	// Constructors and Destructor
	Sprite();
	Sprite(float x, float y, float speeds);
	~Sprite();

	// Functions
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	bool IsInitialized();
	virtual void Draw(float gameTime, D3DXVECTOR3 position);
private:
	LPDIRECT3DTEXTURE9 _texture;
	LPD3DXSPRITE _sprite;

	// Atributes
	D3DCOLOR _color;
	bool _initialized;
	float _speed;
};


#endif // SPRITE_H