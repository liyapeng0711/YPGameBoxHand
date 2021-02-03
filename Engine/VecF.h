#pragma once
#include <math.h>
#include "VecI.h"

class VecF
{
public:
	VecF() = default;
	VecF(float _x, float _y)
		:
		x(_x),
		y(_y)
	{
	}
	VecF operator+(const VecF& rhs)const
	{
		return VecF(x + rhs.x, y + rhs.y);
	}
	VecF operator-(const VecF& rhs)const
	{
		return VecF(x - rhs.x, y - rhs.y);
	}
	VecF operator*(const VecF& rhs)const
	{
		return VecF(x * rhs.x, y * rhs.y);
	}
	VecF operator*(float rhs)const
	{
		return VecF(x*rhs, y*rhs);
	}
	VecF operator/(float rhs)const
	{
		return VecF(x/rhs, y/rhs);
	}
	VecF& operator+=(const VecF& rhs)
	{
		return *this = *this + rhs;
	}
	VecF& operator-=(const VecF& rhs)
	{
		return *this = *this - rhs;
	}
	float GetLengthSq()const
	{
		return x*x + y*y;
	}
	float GetLength()const
	{
		return sqrtf(GetLengthSq());
	}
	VecF GetNormalized()const
	{
		float length = GetLength();
		if (length == 0.0f)
		{
			return *this;
		}
		else
		{
			return *this *(1 / length);
		}
	}
	VecF& Normalized()
	{
		return *this = GetNormalized();
	}
	VecF& ReverseX()
	{
		x = -x;
		return *this;
	}
	VecF& ReverseY()
	{
		y = -y;
		return *this;
	}
	explicit operator VecI()const
	{
		return{ int(x), int(y) };
	}

	//friend class RectF;
public:
	float x;
	float y;
};
