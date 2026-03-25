#include "Animation.h"
#include "GraphicsDevice.h"

Animation::Animation(float frameTime)
{
	this->frameTime = frameTime;
}

Animation::Animation(Texture* tex, float frameTime)
{
	this->texture = tex;
	this->frameTime = frameTime;
	this->currentFrame = 0;
	this->timer = 0;
}

void Animation::AddFrame(int x, int y, int width, int height)
{
	RECT frame{ x, y, x + width, y + height };
	frames.push_back(frame);
}

void Animation::Update(float deltaTime)
{
	if (frames.size() <= 1) return; // Neu chi co 1 frame thi ko can update
	timer += deltaTime;
	if (timer >= frameTime)
	{
		timer = 0;
		currentFrame = (currentFrame + 1) % frames.size();
	}
}

void Animation::Render(LPD3DXSPRITE spriteHandler, D3DXVECTOR3 position)
{
	if (texture && frames.size() > 0) {
		RECT currentFrame = frames[this->currentFrame];
		texture->Render(spriteHandler, &currentFrame, &position);
	}
}

RECT Animation::GetCurrentFrame()
{
	return frames[currentFrame];
}

Animation::~Animation()
{

}