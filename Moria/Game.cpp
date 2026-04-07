#include "Game.h"

Game::Game()
{
	// Constructor
	player = nullptr;
	background = nullptr;
}

Game::~Game()
{
	if (gDevice)
	{
		delete gDevice;
		gDevice = 0;
	}
}

bool Game::Initialize(HWND hWnd)
{
	gDevice = new GraphicsDevice();
	if (!gDevice->Initialize(hWnd, true))
	{
		return false;
	}

	//background = new GameObject();
	//if (!background->Initialize(gDevice->device, L"Forest_Background_0.png"))
	//{
	//	return false;
	//}

	player = new Player(50, 50, 0);
	if (!player->Initialize(L"Player.png", 192, 288))
		return false;

	return true;
}

void Game::Run()
{
	Time::Update();
	Update();
	Draw();
}

void Game::Update()
{
	// Input
	if (GetAsyncKeyState(VK_SPACE))
	{
		PostQuitMessage(0);
	}

	if (player)
	{
		player->Update();
	}
}

void Game::Draw()
{
	// Use XRGB to draw background
	gDevice->Clear(D3DCOLOR_XRGB(0, 100, 120));
	if (gDevice->Begin())
	{
		// Draw background image
		if (background)
		{
			//background->Draw(D3DXVECTOR3(0, 0, 0));
		}
		if (player)
		{
			player->Draw();
		}

		gDevice->End();
		gDevice->Present();
	}
}