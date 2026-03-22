#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include <d3d9.h>

class GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	// Direct3D functions
	bool Initialize(HWND hWInd, bool isWindowed);
	void Clear(D3DCOLOR color);
	void Begin();
	void End();
	void Present();
	
	// short hand for Direct3DDevice9 *device
	LPDIRECT3DDEVICE9 device;
private:
	LPDIRECT3D9 direct3d;
};

#endif // GRAPHICSDEVICE_H