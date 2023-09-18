#include "Goal.h"

Goal::Goal(std::mt19937& rng, Board& brd, Snake& snake)
{
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937& rng, Board& brd, Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, brd.getWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.getHeight() - 1);

	Location new_loc;
	Location new_bigGloc;

	do
	{
		new_loc.x = xDist(rng);
		new_loc.y = yDist(rng);

	} while (snake.HasTouchedGoal(new_loc));

	loc = new_loc;

	do
	{
		new_bigGloc.x = xDist(rng);
		new_bigGloc.y = yDist(rng);

	} while (snake.HasTouchedGoal(new_bigGloc) || new_bigGloc == new_loc);

	bigGloc = new_bigGloc;
}

void Goal::Draw(Board& brd, Location& loc, Color c) const
{
	brd.DrawCell(loc, c);
}


Location& Goal::GetLocation() 
{
	return loc;
}

Location& Goal::BigGGetLocation()
{
	return bigGloc;
}

const Color& Goal::GetGoalColor() const
{
	return c;
}

const Color& Goal::GetBigGoalColor() const
{
	return bigGoalC;
}

