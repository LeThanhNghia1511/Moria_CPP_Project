#include "Sprite.h"

Sprite::Sprite()
{
	// Set the color to white -> we can see the exactly shape of the image
	_color = D3DCOLOR_ARGB(255, 255, 255, 255);
	HRESULT hr = D3DXCreateSprite(GraphicsDevice::GetInstance()->device, &_sprite);

	// Not initialize yet
	_initialized = false;
	_texture = new Texture();
}

bool Sprite::Initialize(LPDIRECT3DDEVICE9 device, std::wstring file, int width, int height)
{
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
    if (_texture)
    {
        RECT* srect = nullptr;
        RECT tempRect;

        if (_currentAnimation)
        {
            tempRect = _currentAnimation->GetCurrentFrame();
            srect = &tempRect;
        }

        _texture->Render(
            GraphicsDevice::GetInstance()->GetSpriteHandler(),
            srect,
            &position,
            D3DCOLOR_XRGB(255, 255, 255)
        );
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