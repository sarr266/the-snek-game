#include "Board.h"

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
