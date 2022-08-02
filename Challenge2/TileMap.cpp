#include "TileMap.h"
#include <vector>
#include <map>
#include <iostream>
#include "Coordinate.h"

using std::vector; using std::map;
using std::cout; using std::endl;

typedef std::pair<Coordinate, Coordinate> CoordinatePair;
typedef std::pair<Coordinate, int> CoordinateScore;

void TileMap::BuildTileArray()
{
	_tileArr = new Tile * [_height];
	for (int i = 0; i < _height; ++i) _tileArr[i] = new Tile[_width];
}

vector<Coordinate> TileMap::GetAdjacent(Coordinate c)
{
	vector<Coordinate> result;

	if (c.getNorth().second >= 0) result.push_back(c.getNorth());
	if (c.getEast().first < _width) result.push_back(c.getEast());
	if (c.getSouth().second < _height) result.push_back(c.getSouth());
	if (c.getWest().first >= 0) result.push_back(c.getWest());
	
	FilterPassableTiles(result);

	return result;
}

void TileMap::FilterPassableTiles(vector<Coordinate>& coordList)
{
	for (vector<Coordinate>::iterator it = coordList.begin(); it < coordList.end(); it++)
		if (GetTile(*it).IsPassable() == false)
			coordList.erase(it);
}

Coordinate TileMap::FindLowestCost(vector<Coordinate>& coordList)
{
	int lowestCost = INT_MAX;
	Coordinate result;

	for (vector<Coordinate>::iterator it = coordList.begin(); it < coordList.end(); it++)
	{
		int cost = GetTile(*it).GetCost();
		if (cost < lowestCost)
		{
			lowestCost = cost;
			result = *it;
		}
	}
	return result;
}

void TileMap::Draw()
{
	for (int i = 0; i < _height; ++i)
	{
		for (int j = 0; j < _width; ++j)
		{
			if (Coordinate(i, j) == _start) cout << 'S';
			else if (Coordinate(i, j) == _goal) cout << 'G';
			else if (IsCoordInPath(Coordinate(i, j))) cout << '$';
			else if (GetTile(i, j).IsPassable()) cout << '.';
			else cout << '#';
		}
		cout << endl;
	}
}

std::vector<Coordinate> TileMap::ReconstructPath(map<Coordinate, Coordinate> cameFrom, Coordinate current)
{
	std::vector<Coordinate> totalPath = { current };
	while (cameFrom.find(current) != cameFrom.end())
	{
		current = cameFrom[current];
		totalPath.push_back(current);
	}
	return totalPath;
}

bool TileMap::FindPath(Coordinate start, Coordinate goal)
{
	vector<Coordinate> openSet = { start };

	map<Coordinate, Coordinate> cameFrom;

	map<Coordinate, int> gScore;
	gScore[start] = 0;

	map<Coordinate, int> fScore;
	fScore[start] = int(start.Distance(goal));

	while (!openSet.empty())
	{
		Coordinate current = FindLowestCost(openSet);
		if (current == goal)
		{
			_start = start;
			_goal = goal;
			_path = ReconstructPath(cameFrom, current);
			return true;
		}

		openSet.erase(std::find(openSet.begin(), openSet.end(), current));

		for (auto neighbor : GetAdjacent(current))
		{
			int tentative_gScore = gScore.find(current)->second + GetCost(neighbor);
			if (gScore.find(neighbor) == gScore.end()) gScore[neighbor] = INT_MAX;
			if (tentative_gScore < gScore.find(neighbor)->second)
			{
				cameFrom[neighbor] = current;
				gScore[neighbor] = tentative_gScore;
				fScore[neighbor] = tentative_gScore + neighbor.Distance(goal);
				if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end())
				{
					openSet.push_back(neighbor);
				}
			}
		}
	}
}