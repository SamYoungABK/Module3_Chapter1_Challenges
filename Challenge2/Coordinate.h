#pragma once
#include <utility>
#include <ctgmath>

const std::pair<int, int> north = std::pair<int, int>(0, -1);
const std::pair<int, int> east = std::pair<int, int>(1, 0);
const std::pair<int, int> south = std::pair<int, int>(0, 1);
const std::pair<int, int> west = std::pair<int, int>(-1, 0);

class Coordinate : public std::pair<int, int>
{
public:

	Coordinate(int x, int y) :
		std::pair<int,int>(x,y)
	{};

	Coordinate(std::pair<int, int> p) :
		std::pair<int, int>(p)
	{};

	Coordinate() {};

	operator std::pair<int, int>() const { return std::pair<int, int>(first, second); };

	Coordinate operator+(Coordinate rhs) { return Coordinate(first + rhs.first, second + rhs.second); };
	Coordinate operator+=(Coordinate rhs) { first + rhs.first; second + rhs.second; return *this; };

	Coordinate operator-(Coordinate rhs) { return Coordinate(first - rhs.first, second - rhs.second); };
	Coordinate operator-=(Coordinate rhs) { first - rhs.first; second - rhs.second; return *this; };

	Coordinate getNorth() { return *this + north; };
	Coordinate getEast() { return *this + east; };
	Coordinate getSouth() { return *this + south; };
	Coordinate getWest() { return *this + west; };

	float Slope(Coordinate rhs) { return (rhs.second - second) / (rhs.first - first); };

	int Distance(Coordinate rhs)
	{
		int xDiff = rhs.first - first;
		int yDiff = rhs.second -second;

		return sqrt(xDiff*xDiff + yDiff*yDiff);
	};
};

