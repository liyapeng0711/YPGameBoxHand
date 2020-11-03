#include "RectI.h"
#include <assert.h>

RectI::RectI(int left_in, int right_in, int top_in, int bottom_in)
	:
	left(left_in), right(right_in), top(top_in), bottom(bottom_in)
{
	assert(right >= left && bottom >= top);
}

RectI::RectI(const VecI & topLeft, const VecI & bottomRight)
	:
	RectI(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

RectI::RectI(const VecI & topLeft, int width, int height)
	:
	RectI(topLeft, topLeft + VecI(width, height))
{
}

RectI RectI::FromCenter(const VecI & center, int halfWidth, int halfHeight)
{
	const VecI offset(halfWidth, halfHeight);
	return RectI(center - offset, center + offset);
}

RectI RectI::GetExpanded(int offset) const
{
	return RectI(left - offset, right + offset, top - offset, bottom + offset);
}

bool RectI::IsOverlappingWith(const RectI & other) const
{
	return left<other.right&&right>other.left&&top<other.bottom&&bottom>other.top;
}

VecI RectI::GetCenter() const
{
	return{ (left + right) / 2, (top + bottom) / 2 };
}

int RectI::GetWidth() const
{
	return right - left;
}

int RectI::GetHeight() const
{
	return bottom - top;
}

bool RectI::IsContainedBy(const RectI & other) const
{
	return top >= other.top&&bottom <= other.bottom&&left >= other.left&&right <= other.right;
}

bool RectI::Contains(const VecI & point)
{
	return point.x >= left&&point.x < right&&point.y >= top&&point.y < bottom;
}
