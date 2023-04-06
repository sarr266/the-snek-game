#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(Location loc, Color c);
	int getWidth();
	int getHeight();
	bool isInsideBoard(const Location& loc);
private:
	static constexpr int dimension = 20;
	static constexpr int width = 20;
	static constexpr int height = 20;
	static constexpr int cellPadding = 1;
	Graphics& gfx;
};
