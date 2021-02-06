#pragma once
#include "Vec2.h"
#include <assert.h>

template<typename T>
class Rect
{
public:
	Rect() = default;
	Rect(T left_in, T right_in, T top_in, T bottom_in)
		:
		left(left_in), right(right_in), top(top_in), bottom(bottom_in)
	{
		assert(right >= left && bottom >= top);
	}
	Rect(const VecI & topLeft, const VecI & bottomRight)
		:
		Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
	{
	}
	Rect(const VecI & topLeft, T width, T height)
		:
		Rect(topLeft, topLeft + VecI(width, height))
	{
	}
	Rect FromCenter(const VecI & center, T halfWidth, T halfHeight)
	{
		const VecI offset(halfWidth, halfHeight);
		return Rect(center - offset, center + offset);
	}
	Rect GetExpanded(T offset) const
	{
		return Rect(left - offset, right + offset, top - offset, bottom + offset);
	}
	bool IsOverlappingWith(const Rect & other) const
	{
		return left<other.right&&right>other.left&&top<other.bottom&&bottom>other.top;
	}
	VecI GetCenter() const
	{
		return{ (left + right) / 2, (top + bottom) / 2 };
	}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - top;
	}
	bool IsContainedBy(const Rect & other) const
	{
		return top >= other.top&&bottom <= other.bottom&&left >= other.left&&right <= other.right;
	}
	bool Contains(const VecI & poT)
	{
		return poT.x >= left&&poT.x < right&&poT.y >= top&&poT.y < bottom;
	}
public:
	T left;
	T right;
	T top;
	T bottom;
};

typedef Rect<int> RectI;
typedef Rect<float> RectF;
