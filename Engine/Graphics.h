/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Rect.h"
#include "Surface.h"

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y)const;
	void Swap(int& a, int& b)const;
	void DrawRect(int x0, int y0, int x1, int y1, Color c);
	void DrawRectDim(int x, int y, int width, int height, Color c)
	{
		DrawRect(x, y, x + width, y + height, c);
	}
	void DrawRectDimWithPadding(int x, int y, int width, int height, Color c, int padding);
	void DrawRectDimWithPadding(int x, int y, int width, int height, Color c, int padding, Color paddingColor)
	{
		DrawRectDimWithPadding(x, y, width, height, c, padding);
		DrawRectDim(x, y, width, padding, paddingColor);
		DrawRectDim(x, y, padding, height, paddingColor);
		DrawRectDim(x, y + height - padding, width, padding, paddingColor);
		DrawRectDim(x + width - padding, y, padding, height, paddingColor);
	}
	void DrawRect(const RectF& rect, Color c)
	{
		DrawRect((int) rect.left, (int) rect.top, (int) rect.right, (int) rect.bottom, c);
	}
	void DrawLine(const VecF& p1, const VecF& p2, Color c)
	{
		// from p1 to p2
		const VecF line = p2 - p1;
		float k;
		float b;
		if (line.x != 0)
		{
			k = line.y / line.x;
			b = p1.y - k*p1.x;
		}

		if (abs(line.x) > abs(line.y))
		{
			// count x
			int xMin = (int)p1.x;
			int xMax = (int)p2.x;
			if (xMin > xMax)
			{
				std::swap(xMin, xMax);
			}
			for (int i = xMin; i <= xMax; i++)
			{
				PutPixel(i, int(k*float(i) + b), c);
			}
		}
		else
		{
			// count y
			int yMin = (int)p1.y;
			int yMax = (int)p2.y;
			if (yMin > yMax)
			{
				std::swap(yMin, yMax);
			}

			for (int i = yMin; i <= yMax; i++)
			{
				if (line.x != 0)
				{
					PutPixel(int((float(i) - b) / k), i, c);
				}
				else
				{
					PutPixel(int(p1.x), i, c);
				}
			}
		}
	}
	static RectF GetGfxRectF()
	{
		return RectF(0.0f, (float)ScreenWidth, 0.0f, (float)ScreenHeight);
	}
	static RectI GetGfxRectI()
	{
		return RectI(0, ScreenWidth, 0, ScreenHeight);
	}
	void DrawIsoRightTriUL(int x, int y, int size, Color c);
	void DrawIsoRightTriUR(int x, int y, int size, Color c);
	void DrawIsoRightTriBL(int x, int y, int size, Color c);
	void DrawIsoRightTriBR(int x, int y, int size, Color c);
	template <typename T>
	void DrawSprite(int x, int y, const Surface& surface, T t)
	{
		DrawSprite(x, y, RectI(0, surface.GetWidth(), 0, surface.GetHeight()), surface, t);
	}
	template <typename T>
	void DrawSprite(int x, int y, const RectI& srcRect, const Surface& surface, T t) // draw partial of a pic
	{
		DrawSprite(x, y, srcRect, GetGfxRectI(), surface, t);
	}
	template <typename T>
	void DrawSprite(int x, int y, const RectI& srcRect, const RectI& clip, const Surface& surface, T t) // draw clip of two rect (different from intersection)
	{
		assert(srcRect.left >= 0);
		assert(srcRect.top >= 0);
		assert(srcRect.right <= surface.GetWidth());
		assert(srcRect.bottom <= surface.GetHeight());
		RectI drawRect = srcRect;
		int drawX = x;
		int drawY = y;
		if (x < clip.left)
		{
			drawRect.left += (clip.left - x);
			drawX = clip.left;
		}
		if (y < clip.top)
		{
			drawRect.top += (clip.top - y);
			drawY = clip.top;
		}
		if (x + srcRect.GetWidth() > clip.right)
		{
			drawRect.right -= x + srcRect.GetWidth() - clip.right;
		}
		if (y + srcRect.GetHeight() > clip.bottom)
		{
			drawRect.bottom -= y + srcRect.GetHeight() - clip.bottom;
		}
		for (int i = drawRect.left; i < drawRect.right; ++i)
		{
			for (int j = drawRect.top; j < drawRect.bottom; ++j)
			{
				Color tempC = surface.GetPixel(i, j);
				int xDest = drawX + i - drawRect.left;
				int yDest = drawY + j - drawRect.top;
				t(tempC, xDest, yDest, *this);
			}
		}
	}
	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;
};