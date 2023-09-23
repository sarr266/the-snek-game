#include "Snake.h"
#include "Colors.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors]
	{
		{10, 100, 32},
		{10, 130, 48},
		{18, 160, 48},
		{10, 130, 48}
	};

	for (int i = 0; i < nSegmentsMax; i++)
	{
		segments[i].InitBody(bodyColors[i % nBodyColors]);
	}
	segments[0].InitHead(loc);
}

void Snake::Moveby(Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].Moveby(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		++nSegments;
	}
}

void Snake::Draw(Board& brd)
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

Location Snake::GetNextHeadLocation(Location& delta_loc)
{
	Location l = segments[0].GetLocation();
	l.Add(delta_loc);
	return l;
}

bool Snake::HasTouchedItself(const Location& self_loc)
{
	for (int i = 1; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == self_loc)
		{
			return true;
		}
	}
	return false;
}

bool Snake::HasTouchedGoal(const Location& self_loc)
{
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == self_loc)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const Location& target) const
{
	for (const auto& s : segments)
	{
		if (s.GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color c_in)
{
	c = c_in;
}

void Snake::Segment::Moveby(Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

Location Snake::Segment::GetLocation() const
{
	return loc;
}

