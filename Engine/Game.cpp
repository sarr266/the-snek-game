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
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snek({ 2,2 }),
	goal(rng, brd, snek),
	bigGoal(rng, brd, snek)
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
	if (isGameStarted)
	{
		if (!isGameOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				delta_loc = { 0, -1 };
			}
			if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				delta_loc = { 0, 1 };
			}
			if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				delta_loc = { 1, 0 };
			}
			if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				delta_loc = { -1, 0 };
			}

			++snekMoveCounter;
			++bigGoalCounter;

			if (snekMoveCounter >= snekMovePeriod)
			{
				snekMoveCounter = 0;

				Location next = snek.GetNextHeadLocation(delta_loc);

				if (!(brd.isInsideBoard(next)) || snek.HasTouchedItself(next))
				{
					isGameOver = true;
				}
				else
				{
					bool isEaten = (next == goal.GetLocation());
					if (isEaten)
					{
						snek.Grow();
					}
					snek.Moveby(delta_loc);

					if (isEaten)
					{
						goal.Respawn(rng, brd, snek);
					}

					if (bigGoalCounter >= bigGoalspawn)
					{
						bool isBigGoalEaten = (next == bigGoal.BigGGetLocation());

						if (isBigGoalEaten)
						{
							bigGoal.Respawn(rng, brd, snek);

							if (snekMovePeriod >= 4)
							{
								snekMovePeriod -= 2;
							}
							else
							{
								snekMovePeriod = 2;
							}

							bigGoalCounter = 0;
						}
					}
				}
			}
		}
	}
	else
	{
		isGameStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}

void Game::ComposeFrame()
{
	if (!isGameStarted)
	{
		SpriteCodex::DrawTitle(200, 200, gfx);
	}
	snek.Draw(brd);
	goal.Draw(brd, goal.GetLocation(), goal.GetGoalColor());

	if (bigGoalCounter >= bigGoalspawn)
	{
		bigGoal.Draw(brd, bigGoal.BigGGetLocation(), bigGoal.GetBigGoalColor());
	}

	if (isGameOver)
	{
		SpriteCodex::DrawGameOver(300, 400, gfx);
	}
}
