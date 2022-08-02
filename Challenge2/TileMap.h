#pragma once
#include "Coordinate.h"
#include "Tile.h"
#include <vector>
#include <map>

using std::vector; using std::map;

class TileMap
{
	int _height;
	int _width;
	Tile** _tileArr = nullptr;

	Coordinate _start;
	Coordinate _goal;
	vector<Coordinate> _path;


public:
	void BuildWall(Coordinate location, int length);
	Tile& GetTile(int x, int y) { return _tileArr[x][y]; };
	Tile& GetTile(Coordinate c) { return _tileArr[c.first][c.second]; };
	int GetCost(Coordinate c) { return (_tileArr[c.first][c.second]).GetCost(); };

	void Draw();

	Coordinate FindLowestCost(std::vector<Coordinate>& coordList);
	bool FindPath(Coordinate start, Coordinate goal);
	vector<Coordinate> GetAdjacent(Coordinate c);
	void BuildTileArray();
	std::vector<Coordinate> ReconstructPath(map<Coordinate, Coordinate> cameFrom, Coordinate current);
	vector<Coordinate> FilterPassableTiles(vector<Coordinate> coordList);
	
	bool IsCoordInPath(Coordinate c) { return (std::find(_path.begin(), _path.end(), c) != _path.end()) ? true : false;  };

	TileMap(int width, int height) :
		_width(width),
		_height(height)
	{
		BuildTileArray();
	};
};

