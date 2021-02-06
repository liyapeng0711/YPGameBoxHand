#pragma once
#include "Graphics.h"

namespace SpriteEffect
{
	class Copy
	{
	public:
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx)const
		{
			gfx.PutPixel(xDest, yDest, cSrc);
		}
	};

	class Chroma
	{
	public:
		Chroma(Color c) : chroma(c) {}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx)const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, cSrc);
			}
		}
	private:
		Color chroma = Colors::Magenta;
	};

	class Substitution
	{
	public:
		Substitution(Color c, Color s) : chroma(c), sub(s) {}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx)const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, sub);
			}
		}
	private:
		Color chroma = Colors::Magenta;
		Color sub = Colors::White;
	};

	class Ghost
	{
	public:
		Ghost(Color c) : chroma(c) {}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx)const
		{
			Color cBase = gfx.GetPixel(xDest, yDest);
			Color avgC = cSrc*0.5f + cBase*0.5f;
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, avgC);
			}
		}
	private:
		Color chroma = Colors::Magenta;
	};
}