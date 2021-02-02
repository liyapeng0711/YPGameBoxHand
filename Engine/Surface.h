#pragma once
#include "Colors.h"
#include <string>

class Surface
{
public:
	Surface(int _width, int _height);
	Surface(const std::string& filename);
	Surface(const Surface& _surface);
	~Surface();
	Surface& operator=(const Surface& _surface);
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y)const;
	int GetWidth()const;
	int GetHeight()const;
private:
	Color* pPixels = nullptr;
	int width;
	int height;
};