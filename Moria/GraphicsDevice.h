#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include <d3d9.h>
#include <d3dx9.h>

class GraphicsDevice
{
private:
	static GraphicsDevice* Instance;
	LPDIRECT3D9 direct3d;
	LPD3DXSPRITE spriteHandler;

public:
	GraphicsDevice();
	~GraphicsDevice();

	// Direct3D functions
	LPDIRECT3DDEVICE9 device;
	bool Initialize(HWND hWInd, bool isWindowed);
	void Clear(D3DCOLOR color);
	bool Begin();
	void End();
	void Present();
	LPDIRECT3DDEVICE9 GetDevice();
	static GraphicsDevice* GetInstance();
	LPD3DXSPRITE GetSpriteHandler();
};

#endif // GRAPHICSDEVICE_H