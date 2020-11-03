#pragma once
#include <math.h>

class VecI
{
public:
	VecI() = default;
	VecI(int _x, int _y)
		:
		x(_x),
		y(_y)
	{
	}
	VecI operator+(const VecI& rhs)const
	{
		return VecI(x + rhs.x, y + rhs.y);
	}
	VecI operator-(const VecI& rhs)const
	{
		return VecI(x - rhs.x, y - rhs.y);
	}
	VecI operator*(const VecI& rhs)const
	{
		return VecI(x * rhs.x, y * rhs.y);
	}
	VecI operator*(int rhs)const
	{
		return VecI(x*rhs, y*rhs);
	}
	VecI& operator+=(const VecI& rhs)
	{
		return *this = *this + rhs;
	}
	VecI& operator-=(const VecI& rhs)
	{
		return *this = *this - rhs;
	}
	VecI& ReverseX()
	{
		x = -x;
		return *this;
	}
	VecI& ReverseY()
	{
		y = -y;
		return *this;
	}

	//friend class RectF;
public:
	int x;
	int y;
};
