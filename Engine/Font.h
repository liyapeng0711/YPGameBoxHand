#pragma once
#include "Surface.h"
#include "Graphics.h"

class Font
{
public:
	Font(const std::string& filename, Color chroma = Colors::White);
	void DrawTextChili(const std::string& text, const VecI& pos, Graphics& gfx, Color c)const;
private:
	RectI MapGlyphRect(char c)const;
private:
	Surface surface;
	int glyphWidth;
	int glyphHeight;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	Color chroma;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};