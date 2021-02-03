#pragma once
#include "Surface.h"
#include "Graphics.h"
#include <vector>

class Animation
{
public:
	Animation(int x, int y, int width, int height, int count, const Surface& sprite, float holdTime, Color chroma = Colors::Magenta);
	void Update(float dt);
	void Draw(const VecI& pos, Graphics& gfx)const;
	void Draw(const VecI& pos, Graphics& gfx, const RectI& clip)const;
private:
	void Advance();
private:
	Color chroma;
	const Surface& sprite;
	std::vector<RectI> frames;
	int iCurFrame = 0;
	float holdTime;
	float curFrameTime = 0;
};