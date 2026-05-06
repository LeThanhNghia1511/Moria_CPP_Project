#include "GameObject.h"

GameObject::GameObject()
{
	transform = new Transform();
	transform->position = D3DXVECTOR3(0, 0, 0);
	sprite = nullptr;
	spriteHandler = nullptr;
}

GameObject::GameObject(float x, float y, float z)
{
	transform = new Transform();
	transform->position = D3DXVECTOR3(x, y, z);

	sprite = nullptr;        
	spriteHandler = nullptr;
}

bool GameObject::Initialize(std::wstring file, int width, int height)
{
	if (!sprite)
	{
		LPDIRECT3DDEVICE9 device = GraphicsDevice::GetInstance()->device;
		spriteHandler = GraphicsDevice::GetInstance()->GetSpriteHandler();
		sprite = new Sprite();
		if (!sprite->Initialize(device, file))
		{
			return false;
		}
	}
	transform->scale.x = width;
	transform->scale.y = height;

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

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	LPDIRECT3DDEVICE9 device = GraphicsDevice::GetInstance()->GetDevice();
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	this->Render(spriteHandler);
	spriteHandler->End();
}

void GameObject::Render(LPD3DXSPRITE spriteHandler)
{
	D3DXVECTOR3 origin(0.0f, 0.0f, 0.0f);
	sprite->Draw(spriteHandler, origin);
}

GameObject::~GameObject()
{
	if (sprite)
	{
		delete sprite;
		sprite = 0;
	}
}