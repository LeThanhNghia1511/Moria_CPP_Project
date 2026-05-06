#ifndef INPUT_H
#define INPUT_H
#define DIRECTINPUT_VERSION 0x0800

#include<string>
#include <d3dx9.h>
#include <dinput.h>

class Input
{
private:
	static Input* Instance;
	LPDIRECTINPUT8 di;
	LPDIRECTINPUTDEVICE8 diKeyboard;
	BYTE keyStates[256];

public:
	static Input* GetInstance();
	float GetAxis(std::string axis);
	bool GetKey(int dikCode);

	Input();
	bool Initialize(HINSTANCE hInstancne, HWND hWnd);
	void Update();
	void Shutdown();
};

#endif

