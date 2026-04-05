#include "AnimationClip.h"

AnimationClip::AnimationClip(Texture* texture, int clipIndex, int totalFrame, float frameTime, int width, int height)
{
	this->frameTime = frameTime;
	this->texture = texture;
	this->timer = 0;

	AddFrame(clipIndex, totalFrame, width, height);
}

AnimationClip::~AnimationClip()
{

}

void AnimationClip::AddFrame(int index, int totalFrame, int width, int height)
{
	for (int i = 0; i < totalFrame; i++)
	{
		RECT frame;
		frame.left = i * width;
		frame.top = index * height;
		frame.right = frame.left + width;
		frame.bottom = frame.top + height;
		frames.push_back(frame);
	}
}

void AnimationClip::Update(float frameTime)
{
	if (frames.size() <= 1) return; // If there is only 1 frame, no need to update
	timer += frameTime;
	if (timer >= this->frameTime)
	{
		timer = 0;
		currentFrame = (currentFrame + 1) % frames.size();
	}
}

void AnimationClip::Render(LPD3DXSPRITE spriteHandler, D3DXVECTOR3 position)
{
	if (texture && frames.size() > 0) {
		RECT frame = frames[this->currentFrame];
		texture->Render(spriteHandler, &frame, &position);
	}
}