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

	player = new Player();
	if (!player->Initialize(L"Player.png", 500, 500))
		return false;

	background = new Sprite();
	if (!background->Initialize(gDevice->device, L"Forest_Background_0.png", 1280, 1080))
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
	if (gDevice->Begin())
	{
		LPD3DXSPRITE spriteHandler = GraphicsDevice::GetInstance()->GetSpriteHandler();

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);


		// Draw background image
		if (background)
		{
			background->Draw(gameTime, D3DXVECTOR3(0, 0, 0));
		}
		if (player)
		{
			player->Draw(gameTime);
		}

		spriteHandler->End();

		gDevice->End();
		gDevice->Present();
	}
}