#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include <windows.h>
#include "Texture.h"

class Animation
{
private:
	std::vector<RECT> frames;
	int currentFrame = 0;
	float frameTime;
	float timer;
	Texture* texture;
public:
	Animation(float frameTime);
	Animation(Texture* tex, float frameTime);
	~Animation();
	void AddFrame(int x, int y, int width, int height);
	void Update(float deltaTime);
	void Render(LPD3DXSPRITE spriteHandler, D3DXVECTOR3 position);
	RECT GetCurrentFrame();
};


#endif

