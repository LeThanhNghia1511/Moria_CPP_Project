#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "Vector3.h"
#include "GraphicsDevice.h"

class Texture
{
private:
	LPDIRECT3DTEXTURE9 _texture;
	D3DXIMAGE_INFO _info; // the texture's information: height, width,...
public:
	Texture();
	~Texture();

	bool Load(LPDIRECT3DDEVICE9 device, std::wstring filePath, int width, int height);

	void Render(LPD3DXSPRITE spriteHandler, RECT* sourceRect, D3DXVECTOR3* position, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	int GetWidth() { return _info.Width; }
	int GetHeight() { return _info.Height; }
	LPDIRECT3DTEXTURE9 GetD3DTexture() { return _texture; }
};


#endif