#include <windows.h>

bool running = true;

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = NULL;
	switch (uMsg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
		{
			running = false;		
		}break;
		default:
		{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Create Window Class
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = L"Moria Window";
	windowClass.lpfnWndProc = WindowCallback;

	// Register Window Class
	RegisterClass(&windowClass);

	// Create Window
	HWND hWindow = CreateWindow(
		windowClass.lpszClassName, // Window class name
		L"My Game Window",	// Title  
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 		// Window type
		CW_USEDEFAULT, CW_USEDEFAULT, // The position that the window will be created at
		1280, 720,				// Height and Width of the window
		NULL,				
		NULL,
		hInstance,			// Program instance
		NULL
	);

	while (running)
	{
		// Input
		MSG message;
		while (PeekMessage(&message, hWindow, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		// Simulate

		// Render
	}
}