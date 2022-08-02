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

	if (c.GetNorth().second >= 0) result.push_back(c.GetNorth());
	if (c.GetEast().first < _width) result.push_back(c.GetEast());
	if (c.GetSouth().second < _height) result.push_back(c.GetSouth());
	if (c.GetWest().first >= 0) result.push_back(c.GetWest());
	
	result = FilterPassableTiles(result);

	return result;
}

vector<Coordinate> TileMap::FilterPassableTiles(vector<Coordinate> coordList)
{
	vector<Coordinate> result;
	for (vector<Coordinate>::iterator it = coordList.begin(); it < coordList.end(); it++)
		if (GetTile(*it).IsPassable())
		{
			result.push_back(*it);
		}
			
	return result;
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
	for (int j = 0; j <= _width+1; ++j) cout << char(219);
	cout << endl;
	for (int i = 0; i < _height; ++i)
	{
		cout << char(219);
		for (int j = 0; j < _width; ++j)
		{
			if (Coordinate(i, j) == _start) cout << 'S';
			else if (Coordinate(i, j) == _goal) cout << 'G';
			else if (IsCoordInPath(Coordinate(i, j))) cout << '*';
			else if (GetTile(i, j).IsPassable()) cout << ' ';
			else cout << char(219);
		}
		cout << char(219);
		cout << endl;
	}
	for (int j = 0; j <= _width+1; ++j) cout << char(219);
	cout << endl;
}

void TileMap::BuildWall(Coordinate location, int length)
{
	int builtLength = 0;
	while (builtLength < length)
	{
		GetTile(location).MakeWall();
		location = location.GetEast();
		builtLength++;
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