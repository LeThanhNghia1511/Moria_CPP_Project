#include "Game.h"

Game::Game()
{
	// Constructor
}

Game::~Game()
{
	if (player)
	{
		delete player;
		player = 0;
	}

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

	player = new GameObject(100, 200, 90, 100.0f, 100.0f);
	if (!player->Initialize(gDevice->device, "EggPlant.png", 64, 64))
	{
		return false;
	}

	time = new Time();
	if (!time->Initialize())
	{
		return false;
	}

	return true;
}

void Game::Run()
{
	// Get game time and Update + Draw
	time->Update();

	Update(time->deltaTime);
	Draw(time->deltaTime);
}

void Game::Update(float gameTime)
{
	// Input
	if (GetAsyncKeyState(VK_SPACE))
	{
		PostQuitMessage(0);
	}

	// Update sprites and other game logic 
	if (player)
	{
		player->HandleInput();
		player->Update(gameTime);
	}
}

void Game::Draw(float gameTime)
{
	// Use XRGB to draw background
	gDevice->Clear(D3DCOLOR_XRGB(0, 100, 120));
	gDevice->Begin();

	// Draw the player
	if (player)
	{
		player->Draw(gameTime);
	}

	gDevice->End();
	gDevice->Present();
}