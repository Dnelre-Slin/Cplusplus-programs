#include <iostream>
#include "Coord.h"
#include "Point2D.h"
#include "Operators.h"

int main()
{
	Point2D point1(Coord2D(2,4));
	std::cout << point1 << '\n';

	Line2D line1(point1, Point2D(Coord2D(5,6)));
	std::cout << line1 << '\n';

	Polygon2D polygon1(Point2D(3, 3), Point2D(4, 7), Point2D(9, 2));
	std::cout << polygon1 << '\n';

	polygon1 += Point2D(5, 5);

	std::cout << polygon1 << '\n';

	system("pause");
	return 0;
}