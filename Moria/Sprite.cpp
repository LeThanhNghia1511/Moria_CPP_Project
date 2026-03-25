#include "Sprite.h"

Sprite::Sprite()
{
	// Set the color to white -> we can see the exactly shape of the image
	_color = D3DCOLOR_ARGB(255, 255, 255, 255);
	HRESULT hr = D3DXCreateSprite(GraphicsDevice::GetInstance()->device, &_sprite);
	_speed = 0;

	// Not initialize yet
	_initialized = false;
	_texture = new Texture();
}

bool Sprite::Initialize(LPDIRECT3DDEVICE9 device, std::wstring file, int width, int height)
{
	// This function is the same as D3DXCreateTextureFromFile Except the width and height are manually enterd
	_texture->Load(device, file, width, height);

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
		_sprite->Draw(_texture->GetD3DTexture(), NULL, NULL, &position, _color);
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
		_texture = 0;
	}
}