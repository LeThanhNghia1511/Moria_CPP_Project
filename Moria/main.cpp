#include <windows.h>
#include "GraphicsDevice.h"
#include "Sprite.h"
#include "Game.h"

#define VK_AKEY 0x41

// Generic GeneratreWindow Functions
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y, int width, int height, HWND& hWnd);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Game Pointer
Game* game;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;

	if (GenerateWindow(hInstance, nCmdShow, "Moria", "Window Title", 1280, 720, hWnd) &&
		Input::GetInstance()->Initialize(hInstance, hWnd))
	{
		game = new Game();
		MSG msg = { 0 };
		if (game->Initialize(hWnd))
		{
			while (true)
			{
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					if (msg.message == WM_QUIT) break;
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					Input::GetInstance()->Update();
					game->Run();
				}
			}
		}

		Input::GetInstance()->Shutdown();
		delete game;
		return (int)msg.wParam;
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
	default:
	{
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return result;
}