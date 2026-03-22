#include <windows.h>
#include "GraphicsDevice.h"
#include "Sprite.h"
#include "Game.h"

#define VK_AKEY 0x41

// Generic GeneratreWindow Functions
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y, int width, int height, HWND& hWnd);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Update and Draw
void Update(float gameTime);
void Draw(GraphicsDevice* gDevice, float gameTime);

bool InitializeInput();

// Game Pointer
Game* game;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;

	if (GenerateWindow(hInstance, nCmdShow, "Moria", "Window Title", 1280, 720, hWnd) && InitializeInput())
	{
		MSG msg;
		game = new Game();
		if (game->Initialize(hWnd))
		{
			while (true)
			{
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				if (msg.message == WM_QUIT)
					break;
				else
				{
					// Update and Draw
					game->Run();
				}
			}
		}

		delete game;
		return msg.wParam;
	}
	return 0;
}


bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd)
{
	return GenerateWindow(hInstance, nCmdShow, className, windowTitle, (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - height) / 2, width, height, hWnd);
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y, int width, int height, HWND& hWnd)
{
	WNDCLASSEX wcex;

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&wcex))
	{
		return false;
	}

	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	return true;
}

bool InitializeInput()
{
	RAWINPUTDEVICE rawInput[1];

	rawInput[0].usUsagePage = 0x01;
	rawInput[0].usUsage = 0x06;
	rawInput[0].dwFlags = 0;
	rawInput[0].hwndTarget = 0;

	if (RegisterRawInputDevices(rawInput, 1, sizeof(rawInput[0])) == false)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = NULL;
	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}break;
	/*case WM_INPUT:
	{
		UINT dwSize;

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

		LPBYTE lpb = new BYTE[dwSize];

		if (lpb == NULL)
		{
			return 0;
		}

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

		RAWINPUT* raw = (RAWINPUT*)lpb;

		if (raw->header.dwType == RIM_TYPEKEYBOARD)
		{
			if (raw->data.keyboard.Message == WM_KEYDOWN || raw->data.keyboard.Message == WM_SYSKEYDOWN)
			{
				std::string information =
					"Make code - " + std::to_string(raw->data.keyboard.MakeCode) +
					"; Flags - " + std::to_string(raw->data.keyboard.Flags) +
					"; Reserved - " + std::to_string(raw->data.keyboard.Reserved) +
					"; Extra Information - " + std::to_string(raw->data.keyboard.ExtraInformation) +
					"; Message - " + std::to_string(raw->data.keyboard.Message) +
					"; VKey - " + std::to_string(raw->data.keyboard.VKey) +
					"\n";

				OutputDebugString(information.c_str());

				if (raw->data.keyboard.VKey == VK_AKEY)
				{
					MessageBox(NULL, "Space key was pressed", NULL, NULL);
				}
			}
		}

	}break;*/
	default:
	{
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return result;
}