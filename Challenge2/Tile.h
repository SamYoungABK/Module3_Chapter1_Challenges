#pragma once
#include "Coordinate.h"

class Tile
{
	Coordinate pos;
	int _cost;
	bool _passable;

public:

	Tile(int cost=0, bool walkable=true) :
		_cost(cost),
		_passable(walkable) 
	{};


	void MakeWall() { _passable = false; };
	int GetCost() { return _cost; };
	bool IsPassable() { return _passable; };
};

