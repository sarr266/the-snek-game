#include "Board.h"
#include "Snake.h"
#include "Goal.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(Location loc, Color c)
{
	gfx.DrawRectDim(loc.x * dimension + cellPadding, loc.y * dimension + cellPadding, dimension - cellPadding, dimension - cellPadding, c);
}

int Board::getWidth()
{
	return width;
}

int Board::getHeight()
{
	return height;
}

bool Board::isInsideBoard(const Location& loc)
{
	return loc.x >= 0 && loc.x < Board::getWidth()
		&& loc.y >= 0 && loc.y < Board::getHeight();
}

bool Board::checkForObstacle(const Location& loc) const
{
	return hasObstacle[loc.y * width + loc.x];
}

void Board::spawnObstacle(std::mt19937& rng, const Snake& snake, Goal& goal)
{
	std::uniform_int_distribution<int> xDist(0, getWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, getHeight() - 1);

	Location newLoc;

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || checkForObstacle(newLoc) || goal.GetLocation() == newLoc || goal.BigGGetLocation() == newLoc);

	hasObstacle[newLoc.y * width + newLoc.x] = true;
}


void Board::drawObstacles()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (checkForObstacle({x, y}))
			{
				DrawCell({ x,y }, obstacleColor);
			}
		}
	}
}
