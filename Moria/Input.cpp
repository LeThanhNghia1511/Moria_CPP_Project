#include "Input.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
// Van chua chinh xac duoc ham GetAxis, cac gia tri return van dang la so nguyen

Input* Input::Instance = nullptr;

Input::Input()
{
	di = nullptr;
	diKeyboard = nullptr;
	ZeroMemory(keyStates, sizeof(keyStates));
}

bool Input::Initialize(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&di, nullptr);
	if (FAILED(hr)) return false;

	hr = di->CreateDevice(GUID_SysKeyboard, &diKeyboard, nullptr);
	if (FAILED(hr)) return false;

	hr = diKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) return false;

	hr = diKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) return false;

	diKeyboard->Acquire();
	return true;
}

void Input::Update()
{
	HRESULT hr = diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)&keyStates);
	if (FAILED(hr))
		diKeyboard->Acquire();
}

void Input::Shutdown()
{
	if (diKeyboard)
	{
		diKeyboard->Unacquire();
		diKeyboard->Release();
		diKeyboard = nullptr;
	}

	if (di)
	{
		di->Release();
		di = nullptr;
	}
}

bool Input::GetKey(int dikCode)
{
	// 0x80 la 1000 0000, neu 1 so duoc nhan vao thi bit dau tien la so 1
	return (GetInstance()->keyStates[dikCode] & 0x80) > 0;
}

float Input::GetAxis(std::string axis)
{
	if (axis == "Horizontal")
	{
		// GetInput (A - D)
		if (GetKey(DIK_LEFT) || GetKey(DIK_A))
		{
			return -1;
		}
		if (GetKey(DIK_RIGHT) || GetKey(DIK_D))
		{
			return 1;
		}
		return 0;
	}
	if (axis == "Vertical")
	{
		// GetInput (W - S)
		if (GetKey(DIK_UP) || GetKey(DIK_W))
		{
			return -1;
		}
		if (GetKey(DIK_DOWN) || GetKey(DIK_S))
		{
			return 1;
		}
		return 0;
	}
}

Input* Input::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new Input();
	}
	return Instance;
}