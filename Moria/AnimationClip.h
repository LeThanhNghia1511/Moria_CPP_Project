#pragma once
#include <vector>
#include "Texture.h"
#include "Time.h"
#include <windows.h>

class AnimationClip
{
private:
	std::vector<RECT> frames; // Map to store clip index and its name
	int currentFrame = 0;
	float frameTime; // The time between each clips
	float timer; // To count the time 
	std::string clipName;
	Texture* texture;

public:
	// Constructor & Destructor
	AnimationClip(Texture* texture, int clipIndex, int totalFrame, float frameTime, int width, int height);
	~AnimationClip();

	void AddFrame(int index, int totalFrame, int width, int height);
	void Update();
	void Render(LPD3DXSPRITE spriteHandler, D3DXVECTOR3 position);
};