#pragma once

#include "Snake.h"
#include "Board.h"
#include "Location.h"
#include "Colors.h"
#include <random>
class Goal
{
public:
	Goal(std::mt19937& rng, Board& brd, Snake& snake);
	void Respawn(std::mt19937& rng, Board& brd, Snake& snake);
	void Draw(Board& brd, Location& loc, Color c) const;
	Location& GetLocation();
	Location& BigGGetLocation();
	const Color& GetGoalColor() const;
	const Color& GetBigGoalColor() const;
private:
	Location loc;
	Location bigGloc;
	static constexpr Color c = Colors::Red;
	static constexpr Color bigGoalC = Colors::Cyan;

};
