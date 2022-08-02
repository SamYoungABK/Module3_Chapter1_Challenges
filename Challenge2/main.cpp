#include "TileMap.h"
#include <chrono>
#include <iostream>
#include "time.h"

using namespace std::chrono;
using std::cout; using std::endl;

int main()
{
	TileMap t(20,20);
	t.BuildWall(Coordinate(3, 5), 13);
	t.BuildWall(Coordinate(0, 3), 7);
	t.BuildWall(Coordinate(0, 9), 7);
	t.BuildWall(Coordinate(9, 9), 7);

	auto start = steady_clock::now();
	t.FindPath(Coordinate(0, 1), (Coordinate(8, 18)));
	auto end = steady_clock::now();
	duration<int, std::nano> diff = end - start;
	t.Draw();

	cout << "Time Taken: " << std::fixed << diff.count() << " nanoseconds" << endl;
}