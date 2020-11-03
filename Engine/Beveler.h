#pragma once
#include "Graphics.h"

class Beveler
{
public:
	Beveler() = default;
	Beveler(Color baseColor_in);
	void DrawOuterBevel(const RectF& rect, int size, Graphics& gfx)const;	// rect contains the bevel, looks like outer
	void DrawInnerBevel(const RectF& rect, int size, Graphics& gfx)const;	// rect contains the bevel, looks like inner
	void DrawBeveledBrick(const RectF& rect, int bevelSize, Graphics& gfx)const;
	void DrawBeveledFrame(const RectF& rect, int bevelSize, Graphics& gfx)const;
	Color GetBaseColor()const;
	void SetBaseColor(Color base_in);

private:
	static constexpr float leftFactor = 1.10f;
	static constexpr float topFactor = 0.93f;
	static constexpr float bottomFactor = 0.80f;
	static constexpr float rightFactor = 0.65f;
	Color baseColor;
	Color leftColor;
	Color topColor;
	Color bottomColor;
	Color rightColor;
};