#include "AnimationController.h"

AnimationController::AnimationController(Texture* texture, int width, int height)
{
	this->texture = texture;
	this->width = width;
	this->height = height;
	currentClip = nullptr;
}

AnimationController::~AnimationController()
{
	for (auto clip : animationClips)
	{
		delete clip.second; // Xóa từng clip đã tạo bằng new
	}
	animationClips.clear();
}

void AnimationController::AddClip(int clipIndex, int totalFrame, float frameTime, std::string clipName)
{

	AnimationClip* newClip = new AnimationClip(texture, clipIndex, totalFrame, frameTime, width, height);
	animationClips.insert({ clipName, newClip });

	if (_isFirstClipCreated == false)
	{
		currentClip = newClip;
		_isFirstClipCreated = true;
	}
}

void AnimationController::Play(LPD3DXSPRITE spriteHandler, D3DXVECTOR3 position)
{
	if (currentClip)
	{
		currentClip->Update();
		currentClip->Render(spriteHandler, position);
	}
}

void AnimationController::ChangeClip(std::string clipName)
{
	currentClip = animationClips[clipName];
}
