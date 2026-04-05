#pragma once
#include "AnimationClip.h"
#include <map>

class AnimationController
{
private:
	std::map<std::string, AnimationClip*> animationClips; // Manage the clips in the animator
	AnimationClip* currentClip; // The current clip that is playing
	float gameTime; // Time to update the animation
	int width, height; // The width and height of each frame in the texture
	Texture* texture;

	bool _isFirstClipCreated = false;

public:
	AnimationController(Texture* texture, int width, int height, float gameTime);
	~AnimationController();

	void AddClip(int clipIndex, int totalFrame, float frameTime, std::string clipName);
	void Play(D3DXVECTOR3 position); // play the current clip
	void ChangeClip(std::string clipName); // change the current clip to a new one
};

