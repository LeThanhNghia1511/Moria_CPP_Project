#include "GameObject.h"

GameObject::GameObject()
{
	transform = new Transform(); // Tạo ra 1 cái duy nhất ở đây thôi
	sprite = nullptr;
	spriteHandler = nullptr;
}

GameObject::GameObject(float x, float y)
{
	transform = new Transform();
	sprite = nullptr;        
	spriteHandler = nullptr;
}

bool GameObject::Initialize(LPDIRECT3DDEVICE9 device, std::wstring file, int width, int height)
{
	if (!sprite)
	{
		spriteHandler = GraphicsDevice::GetInstance()->GetSpriteHandler();
		sprite = new Sprite();
		if (!sprite->Initialize(device, file))
		{
			return false;
		}
	}
	return true;
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
	if (!sprite) return;

	D3DXMATRIX mat = transform->GetWorldMatrix();
	spriteHandler->SetTransform(&mat);

	GraphicsDevice::GetInstance()->device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	GraphicsDevice::GetInstance()->device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	this->Render(spriteHandler);
	spriteHandler->End();
}

GameObject::~GameObject()
{
	if (sprite)
	{
		delete sprite;
		sprite = 0;
	}
}