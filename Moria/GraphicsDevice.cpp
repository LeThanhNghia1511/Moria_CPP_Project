#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice()
{
	// Constructor
}

GraphicsDevice::~GraphicsDevice()
{
	if (device)
	{
		device->Release();
		device = NULL;
	}
	if (direct3d)
	{
		direct3d->Release();
		direct3d = NULL;
	}
}

bool GraphicsDevice::Initialize(HWND hWnd, bool isWindowed)
{
	// create the Direct3D Pointer
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS presentationParams;
	ZeroMemory(&presentationParams, sizeof(presentationParams));
	presentationParams.Windowed = isWindowed;
	presentationParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentationParams.hDeviceWindow = hWnd;

	// Create the device
	if (!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING, &presentationParams, &device)))
	{
		return false;
	}

	return true;
}

void GraphicsDevice::Clear(D3DCOLOR color)
{
	// 2nd parma is set to NULL -> clear the entire backbuffer
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void GraphicsDevice::Begin()
{
	device->BeginScene();
}

void GraphicsDevice::End()
{
	device->EndScene();
}

void GraphicsDevice::Present()
{
	// Present our scene to the window
	device->Present(NULL, NULL, NULL, NULL);
}