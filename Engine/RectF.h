#pragma once
#include "VecF.h"

class RectF
{
public:
	RectF() = default;
	RectF(float left_in, float right_in, float top_in, float bottom_in);
	RectF(const VecF& topLeft, const VecF& bottomRight);
	RectF(const VecF& topLeft, float width, float height);
	static RectF FromCenter(const VecF& center, float halfWidth, float halfHeight);
	RectF GetExpanded(float offset)const;
	bool IsOverlappingWith(const RectF& other)const;
	VecF GetCenter()const;
	float GetWidth()const;
	float GetHeight()const;
	bool IsContainedBy(const RectF& other)const;
public:
	float left;
	float right;
	float top;
	float bottom;
};