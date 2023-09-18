#pragma once
#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(Location loc, Color c);
	int getWidth();
	int getHeight();
	bool isInsideBoard(const Location& loc);
	bool checkForObstacle(const Location& loc) const;
	void spawnObstacle(std::mt19937& rng, const class Snake& snake, class Goal& goal); //forward declaration
	void drawObstacles();
private:
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr int dimension = 20;
	static constexpr int width = 20;
	static constexpr int height = 20;
	static constexpr int cellPadding = 1;
	bool hasObstacle[width * height] = { false };
	Graphics& gfx;
};
