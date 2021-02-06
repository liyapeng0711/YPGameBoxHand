#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, int count, const Surface & sprite, float holdTime, Color chroma)
	:
	sprite(sprite),
	holdTime(holdTime),
	chroma(chroma)
{
	for (int i = 0; i < count; ++i)
	{
		frames.emplace_back(RectI({ x + width*i, y }, width, height));
	}
}

void Animation::Update(float dt)
{
	curFrameTime += dt;
	while (curFrameTime > holdTime)
	{
		Advance();
		curFrameTime -= holdTime;
	}
}

void Animation::Draw(const VecI & pos, Graphics & gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], sprite, chroma);
}

void Animation::Draw(const VecI & pos, Graphics & gfx, const RectI & clip) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], clip, sprite, chroma);
}

void Animation::DrawColor(const VecI & pos, Graphics & gfx, Color c) const
{
	gfx.DrawSpriteSubstitute(pos.x, pos.y, frames[iCurFrame], sprite, c, chroma);
}

void Animation::DrawGhost(const VecI & pos, Graphics & gfx) const
{
	gfx.DrawSpriteGhost(pos.x, pos.y, frames[iCurFrame], sprite, chroma);
}

void Animation::Advance()
{
	if (++iCurFrame == frames.size())
	{
		iCurFrame = 0;
	}
}
