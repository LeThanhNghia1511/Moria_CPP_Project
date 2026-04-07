#ifndef GAME_H
#define GAME_H

#include "GraphicsDevice.h"
#include "GameObject.h"
#include "Time.h"
#include "Player.h"

class Game
{
public:
	// Constructor and Destructor
	Game();
	~Game();

	// Functions
	bool Initialize(HWND hWnd);
	void Run();
	void Update();
	void Draw();

private:
	GraphicsDevice* gDevice;
	GameObject* background;
	Player* player;
};

#endif // GAME_H
