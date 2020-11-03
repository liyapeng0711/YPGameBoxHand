#include "RectF.h"
#include <assert.h>

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in), right(right_in), top(top_in), bottom(bottom_in)
{
	assert(right >= left && bottom >= top);
}

RectF::RectF(const VecF & topLeft, const VecF & bottomRight)
	:
	RectF(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

RectF::RectF(const VecF & topLeft, float width, float height)
	:
	RectF(topLeft, topLeft + VecF(width, height))
{
}

RectF RectF::FromCenter(const VecF & center, float halfWidth, float halfHeight)
{
	const VecF offset(halfWidth, halfHeight);
	return RectF(center - offset, center + offset);
}

RectF RectF::GetExpanded(float offset) const
{
	return RectF(left - offset, right + offset, top - offset, bottom + offset);
}

bool RectF::IsOverlappingWith(const RectF & other) const
{
	return left<other.right&&right>other.left&&top<other.bottom&&bottom>other.top;
}

VecF RectF::GetCenter() const
{
	return{ (left + right) / 2.0f, (top + bottom) / 2.0f };
}

float RectF::GetWidth() const
{
	return right - left;
}

float RectF::GetHeight() const
{
	return bottom - top;
}

bool RectF::IsContainedBy(const RectF & other) const
{
	return top >= other.top&&bottom <= other.bottom&&left >= other.left&&right <= other.right;
}
