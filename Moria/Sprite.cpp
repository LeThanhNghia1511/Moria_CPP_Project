#include "Sprite.h"

Sprite::Sprite()
{
	// Set the color to white -> we can see the exactly shape of the image
	_color = D3DCOLOR_ARGB(255, 255, 255, 255);

	_speed = 0;

	// Not initialize yet
	_initialized = false;
}

Sprite::Sprite(float x, float y, float speed)
{
	// Set the color to white -> we can see the exactly shape of the image
	_color = D3DCOLOR_ARGB(255, 255, 255, 255);

	_speed = speed;

	_speed = 0;

	// Not initialize yet
	_initialized = false;
}

bool Sprite::Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
{
	// This function is the same as D3DXCreateTextureFromFile Except the width and height are manually enterd
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(device, file.c_str(), width, height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &_texture)))
	{
		std::string msg = "Error! The texture image may be not available. Requested image: " + file;
		MessageBox(NULL, msg.c_str(), NULL, NULL);
		return false;
	}
	// Succeded -> Try to create the sprite
	if (!SUCCEEDED(D3DXCreateSprite(device, &_sprite)))
	{
		MessageBox(NULL, "There was an error creating the sprite.", NULL, NULL);
	}

	_initialized = true;
	return true;
}

bool Sprite::IsInitialized()
{
	return _initialized;
}

void Sprite::Draw(float gameTime, D3DXVECTOR3 position)
{
	if (_sprite && _texture)
	{
		_sprite->Begin(D3DXSPRITE_ALPHABLEND);
		_sprite->Draw(_texture, NULL, NULL, &position, _color);
		_sprite->End();
	}
}

Sprite::~Sprite()
{
	if (_sprite)
	{
		_sprite->Release();
		_sprite = 0;
	}
	if (_texture)
	{
		_texture->Release();
		_texture = 0;
	}
}