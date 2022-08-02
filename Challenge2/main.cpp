#include "TileMap.h"

int main()
{
	TileMap t(10,10);
	t.FindPath(Coordinate(3, 1), (Coordinate(8,8)));
	t.Draw();
}