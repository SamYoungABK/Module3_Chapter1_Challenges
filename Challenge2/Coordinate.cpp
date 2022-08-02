#include "Coordinate.h"

constexpr bool operator==(const Coordinate& lhs, const Coordinate& rhs)
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
};