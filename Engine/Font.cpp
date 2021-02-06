#include "Font.h"
#include "SpriteEffect.h"

Font::Font(const std::string & filename, Color chroma)
	:
	surface(filename),
	chroma(chroma)
{
	glyphWidth = surface.GetWidth() / nColumns;
	glyphHeight = surface.GetHeight() / nRows;
}

void Font::DrawTextChili(const std::string & text, const VecI & pos, Graphics & gfx, Color c) const
{
	VecI posChar = pos;
	for (const auto& i : text)
	{
		if (i == '\n')
		{
			posChar.y += glyphHeight;
			posChar.x = pos.x;
		}
		else
		{
			if (i >= firstChar && i <= lastChar)
			{
				if (i != ' ')
				{
					gfx.DrawSprite(posChar.x, posChar.y, MapGlyphRect(i), surface, SpriteEffect::Substitution(chroma, c));
				}
			}
			posChar.x += glyphWidth;
		}
	}
}

RectI Font::MapGlyphRect(char c) const
{
	const int index = c - firstChar;
	const int column = index % nColumns;
	const int row = index / nColumns;
	return RectI({ glyphWidth* column, glyphHeight* row }, glyphWidth, glyphHeight);
}
