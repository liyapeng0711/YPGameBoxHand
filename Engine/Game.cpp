/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
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
#include "MainWindow.h"
#include "Game.h"
#include "assert.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	boy({20.0f, 20.0f}),
	font("Images\\Fixedsys16x28.bmp"),
	enermy({100.0f, 100.0f})
{

}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	// dt
	float dt = ft.Mark();
	// move direction
	VecF dir(0, 0);
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		dir.x -= 1.0f;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		dir.x += 1.0f;
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		dir.y -= 1.0f;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		dir.y += 1.0f;
	}
	boy.SetDirection(dir);
	boy.Update(dt);
	// attack
	if (wnd.kbd.KeyIsPressed(VK_NUMPAD1))
	{
		boy.Fire();
	}
	// enermy update
	if (enermy.IsAlive())
	{	
		// is attacked?
		if (boy.AttackCharacter(enermy.GetRect()))
		{
			enermy.BeDead();
		}
		else
		{
			// move direction
			VecF dir2(0, 0);
			if (wnd.kbd.KeyIsPressed('A'))
			{
				dir2.x -= 1.0f;
			}
			if (wnd.kbd.KeyIsPressed('D'))
			{
				dir2.x += 1.0f;
			}
			if (wnd.kbd.KeyIsPressed('W'))
			{
				dir2.y -= 1.0f;
			}
			if (wnd.kbd.KeyIsPressed('S'))
			{
				dir2.y += 1.0f;
			}
			enermy.SetDirection(dir2);
			enermy.Update(dt);
		}
	}
	// test effect
	while (!wnd.kbd.KeyIsEmpty())
	{
		const auto e = wnd.kbd.ReadKey();
		if (e.IsPress() && e.GetCode() == VK_SPACE)
		{
			boy.ActivateEffect();
			hit.Play();
		}
	}
}

void Game::ComposeFrame()
{	
	font.DrawTextChili("Yapeng Li, Hello!\nNice to meet you:)", wnd.mouse.GetPos(), gfx, Colors::Yellow);
	boy.Draw(gfx);
	if (enermy.IsAlive())
	{
		enermy.Draw(gfx);
	}
}
