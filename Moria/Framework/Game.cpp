#include "Game.h"

Game::Game()
{
	// Khoi tao Graphics device
	gDevice = new GraphicsDevice();
	
	player = nullptr;
	background = nullptr;
	eggplant = nullptr;
	bird = nullptr;
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
	if (!gDevice->Initialize(hWnd, true))
	{
		return false;
	}

	//// Add player
	player = new Player(100, 100, 0);
	if (!player->Initialize(L"Player.png", 2, 2))
		return false;
	player->collider = new Collider(player, 48, 48, 0, 0, false);
	player->rigidbody = new Rigidbody(player, 0.0f, 0.0f); // Mass = 1kg, gravityScale = 1 (bị ảnh hưởng bởi trọng lực bình thường)
	PhysicsWorld::GetInstance()->AddCollider(player->collider);

	// Add background
	background = new GameObject();
	if(!background->Initialize(L"Forest_Background_0.png", 10, 10))
		return false;

	eggplant = new GameObject(100, 100, 0);
	if(!eggplant->Initialize(L"EggPlant.png", 1, 1))
		return false;

	bird = new Bird1(200, 120, 0);
	if (!bird->Initialize(L"Bird_1.png", 2, 2))
		return false;
	bird->collider = new Collider(bird, 48, 48, 0, 0, false);
	bird->rigidbody = new Rigidbody(bird, 1.0f, 0.0f); // Mass = 1kg, gravityScale = 0 (không bị ảnh hưởng bởi trọng lực)
	PhysicsWorld::GetInstance()->AddCollider(bird->collider);

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
	PhysicsWorld::GetInstance()->Step(Time::GetDeltaTime());

	// Update gameObj
	if (player)
	{
		player->Update();
	}

	if (bird)
	{
		bird->Update();
	}
}

void Game::Draw()
{
	gDevice->Clear(D3DCOLOR_XRGB(0, 100, 120));
	if (gDevice->Begin())
	{
		// Draw background 
		if (background)
			background->Draw();

		if (player)
			player->Draw();

		if (eggplant)
			eggplant->Draw();

		if (bird)
			bird->Draw();

		gDevice->End();
		gDevice->Present();
	}
}