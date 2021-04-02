#pragma once
#include <math.h>

template <typename T>
class Vec2
{
public:
	Vec2() = default;
	Vec2(T _x, T _y)
		:
		x(_x),
		y(_y)
	{
	}
	Vec2 operator+(const Vec2& rhs)const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}
	Vec2 operator-(const Vec2& rhs)const
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}
	Vec2 operator*(const Vec2& rhs)const
	{
		return Vec2(x * rhs.x, y * rhs.y);
	}
	Vec2 operator*(T rhs)const
	{
		return Vec2(x*rhs, y*rhs);
	}
	Vec2 operator/(T rhs)const
	{
		return Vec2(x/rhs, y/rhs);
	}
	Vec2& operator+=(const Vec2& rhs)
	{
		return *this = *this + rhs;
	}
	Vec2& operator-=(const Vec2& rhs)
	{
		return *this = *this - rhs;
	}
	T GetLengthSq()const
	{
		return x*x + y*y;
	}
	T GetLength()const
	{
		return std::sqrt(GetLengthSq());
	}
	Vec2 GetNormalized()const
	{
		T length = GetLength();
		if (length == T(0))
		{
			return *this;
		}
		else
		{
			return *this *(T(1) / length);
		}
	}
	Vec2& Normalized()
	{
		return *this = GetNormalized();
	}
	Vec2& ReverseX()
	{
		x = -x;
		return *this;
	}
	Vec2& ReverseY()
	{
		y = -y;
		return *this;
	}
	bool IsZero()const
	{
		return x == T(0) && y == T(0);
	}
	// two methods of convertion: by constructor and operator
	template <typename S>
	explicit Vec2(const Vec2<S>& src)
		:
		x(T(src.x)),
		y(T(src.y))
	{
	}
	template <typename S>
	explicit operator Vec2<S>()const
	{
		return{ S(x), S(y) };
	}

public:
	T x;
	T y;
};

typedef Vec2<int> VecI;
typedef Vec2<float> VecF;