#pragma once
#include "VecI.h"

class RectI
{
public:
	RectI() = default;
	RectI(int left_in, int right_in, int top_in, int bottom_in);
	RectI(const VecI& topLeft, const VecI& bottomRight);
	RectI(const VecI& topLeft, int width, int height);
	static RectI FromCenter(const VecI& center, int halfWidth, int halfHeight);
	RectI GetExpanded(int offset)const;
	bool IsOverlappingWith(const RectI& other)const;
	VecI GetCenter()const;
	int GetWidth()const;
	int GetHeight()const;
	bool IsContainedBy(const RectI& other)const;
	bool Contains(const VecI& point);
public:
	int left;
	int right;
	int top;
	int bottom;
};