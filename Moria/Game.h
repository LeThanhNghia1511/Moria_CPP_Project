#ifndef GAME_H
#define GAME_H

#include "GraphicsDevice.h"
#include "GameObject.h"
#include "Sprite.h"
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
	void Update(float gameTime);
	void Draw(float gameTime);

private:
	GraphicsDevice* gDevice;
	Sprite* background;
	Player* player;
	Time* time;
};

#endif // GAME_H
