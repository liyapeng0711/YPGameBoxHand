#include "Beveler.h"
#include <assert.h>

Beveler::Beveler(Color baseColor_in)
{
	SetBaseColor(baseColor_in);
}

void Beveler::DrawOuterBevel(const RectF & rect, int size, Graphics & gfx) const
{
	assert(rect.GetWidth() >= 2 * size&&rect.GetHeight() >= 2 * size);
	const int rectleft = (int)rect.left;
	const int rectright = (int)rect.right;
	const int recttop = (int)rect.top;
	const int rectbottom = (int)rect.bottom;
	// corner, corner, middle
	// left
	gfx.DrawIsoRightTriBL(rectleft, recttop, size, leftColor);
	gfx.DrawIsoRightTriUL(rectleft, rectbottom - size, size, leftColor);
	gfx.DrawRect(rectleft, recttop + size, rectleft + size, rectbottom - size, leftColor);
	// right
	gfx.DrawIsoRightTriBR(rectright-size, recttop, size, rightColor);
	gfx.DrawIsoRightTriUR(rectright-size, rectbottom - size, size, rightColor);
	gfx.DrawRect(rectright-size, recttop + size, rectright, rectbottom - size, rightColor);
	// top
	gfx.DrawIsoRightTriUR(rectleft, recttop, size, topColor);
	gfx.DrawIsoRightTriUL(rectright-size, recttop, size, topColor);
	gfx.DrawRect(rectleft+size, recttop, rectright - size, recttop + size, topColor);
	// bottom
	gfx.DrawIsoRightTriBR(rectleft, rectbottom-size, size, bottomColor);
	gfx.DrawIsoRightTriBL(rectright-size, rectbottom - size, size, bottomColor);
	gfx.DrawRect(rectleft+size, rectbottom-size , rectright - size, rectbottom, bottomColor);
}

void Beveler::DrawInnerBevel(const RectF & rect, int size, Graphics & gfx) const
{
	assert(rect.GetWidth() >= 2 * size&&rect.GetHeight() >= 2 * size);
	const int rectleft = (int)rect.left;
	const int rectright = (int)rect.right;
	const int recttop = (int)rect.top;
	const int rectbottom = (int)rect.bottom;
	// corner, corner, middle
	// left
	gfx.DrawIsoRightTriBL(rectleft, recttop, size, rightColor);
	gfx.DrawIsoRightTriUL(rectleft, rectbottom - size, size, rightColor);
	gfx.DrawRect(rectleft, recttop + size, rectleft + size, rectbottom - size, rightColor);
	// right
	gfx.DrawIsoRightTriBR(rectright - size, recttop, size, leftColor);
	gfx.DrawIsoRightTriUR(rectright - size, rectbottom - size, size, leftColor);
	gfx.DrawRect(rectright - size, recttop + size, rectright, rectbottom - size, leftColor);
	// top
	gfx.DrawIsoRightTriUR(rectleft, recttop, size, bottomColor);
	gfx.DrawIsoRightTriUL(rectright - size, recttop, size, bottomColor);
	gfx.DrawRect(rectleft + size, recttop, rectright - size, recttop + size, bottomColor);
	// bottom
	gfx.DrawIsoRightTriBR(rectleft, rectbottom - size, size, topColor);
	gfx.DrawIsoRightTriBL(rectright - size, rectbottom - size, size, topColor);
	gfx.DrawRect(rectleft + size, rectbottom - size, rectright - size, rectbottom, topColor);
}

void Beveler::DrawBeveledBrick(const RectF & rect, int bevelSize, Graphics & gfx) const
{
	DrawOuterBevel(rect, bevelSize, gfx);
	gfx.DrawRect(rect.GetExpanded(-float(bevelSize)), baseColor);
}

void Beveler::DrawBeveledFrame(const RectF & rect, int bevelSize, Graphics & gfx) const
{
	DrawOuterBevel(rect, bevelSize, gfx);
	DrawInnerBevel(rect.GetExpanded(-float(bevelSize)), bevelSize, gfx);
}

Color Beveler::GetBaseColor() const
{
	return baseColor;
}

void Beveler::SetBaseColor(Color base_in)
{
	baseColor = base_in;
	leftColor = leftFactor*baseColor;
	rightColor = rightFactor*baseColor;
	topColor = topFactor*baseColor;
	bottomColor = bottomFactor*baseColor;

}
