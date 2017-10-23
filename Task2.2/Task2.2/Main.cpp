#include <iostream>
#include "Polygon2D.h"
#include "Operator Overloads.h"

int main()
{
	Point2D point1(3, 5);

	std::cout << point1 << '\n';

	Line2D line1(Point2D(7, 1), Point2D(2, 6));

	std::cout << line1 << '\n';

	Polygon2D polygon1(Point2D(3, 6), Point2D(9, 2), Point2D(8, 8));
	Polygon2D polygon2(Point2D(8, 1), Point2D(-3, 31), Point2D(12, 16));

	std::cout << polygon1 << " + " << polygon2 << '\n';
	Polygon2D polygon3(polygon1, polygon2);
	std::cout << "= " << polygon1 + polygon2 << '\n';
	std::cout << "Polygon3 = " << polygon3 << '\n';

	Polygon2D polygon4(Point2D(7, 6), line1);
	std::cout << polygon4 << '\n';

	Polygon2D polygon5 = polygon4, polygon6;
	polygon6 = polygon1;

	std::cout << polygon5 << '\n' << polygon6 << '\n';

	Polygon2D polygon7 = line1 + point1;
	std::cout << polygon7 << '\n';

	polygon7 += polygon6;

	std::cout << polygon7 << '\n';

	system("pause");
	return 0;
}