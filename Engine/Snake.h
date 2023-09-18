#pragma once

#include "Location.h"
#include "Colors.h"
#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc); //initialise the head segment
		void InitBody(Color c); //initialise the body
		void Moveby(Location& delta_loc);
		void Follow(const Segment& next); //going to follow the segment that's after it
		void Draw(Board& brd); //to draw the segment
		Location GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc); //constructor for class Snake
	void Moveby(Location& delta_loc); //this is going to move the snake by a certain position
	void Grow(); //the snake is gonna eat stuff and grow
	void Draw(Board& brd); //this is going to draw the snake on the board
	Location GetNextHeadLocation(Location& delta_loc);
	bool HasTouchedItself(const Location& self_loc);
	bool HasTouchedGoal(const Location& self_loc);
	bool IsInTile(const Location& target) const;
private:
	static constexpr Color headColor = Colors::Magenta;
	static constexpr int nSegmentsMax = 100; //max no of segments that we can have
	Segment segments[nSegmentsMax]; //the array of segments
	int nSegments = 1; //keeps track of current segment number
};
