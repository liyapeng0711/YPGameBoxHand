#include "Surface.h"
#include "ChiliWin.h"
#include <fstream>
#include <assert.h>

Surface::Surface(int _width, int _height)
	:
	width(_width),
	height(_height),
	pPixels(new Color[width*height])
{
}

Surface::Surface(const std::string & filename)
{
	std::ifstream file(filename, std::ios::binary);
	assert(file);
	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));
	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));
	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);
	assert(bmInfoHeader.biCompression == BI_RGB);
	width = bmInfoHeader.biWidth;
	height = std::abs(bmInfoHeader.biHeight);
	pPixels = new Color[width*height];
	file.seekg(bmFileHeader.bfOffBits);
	const int padding = (4 - (width * 3) % 4) % 4;	// to make width multiple of 4 in bmp
	bool isHiPositive = bmInfoHeader.biHeight > 0;
	const int yStart = isHiPositive ? (height - 1) : 0;
	const int yEnd = isHiPositive ? -1 : height;
	const int dy = isHiPositive ? -1 : 1;
	for (int i = yStart; i !=yEnd; i+=dy)
	{
		for (int j = 0; j < width; ++j)
		{
			PutPixel(j, i, Color(file.get(), file.get(), file.get()));
		}
		file.seekg(padding, std::ios::cur);
	}

}

Surface::Surface(const Surface & _surface)
{
	*this = _surface;
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

Surface & Surface::operator=(const Surface & _surface)
{
	width = _surface.width;
	height = _surface.height;
	delete[] pPixels;
	pPixels = nullptr;
	pPixels = new Color[width*height];
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			pPixels[j*width + i] = _surface.pPixels[j*width + i];
		}
	}
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y*width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y*width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}
