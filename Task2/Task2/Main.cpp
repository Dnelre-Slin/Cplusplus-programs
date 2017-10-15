#include <iostream>
#include "Point.h"
#include "Line.h"
#include "Polygon.h"

int main()
{
	Point p1(1, 2);
	Point p2(4, 5);
	Point p3(6, 11);

	Line l1 = p1 + p2;

	Polygon poly = p3 + l1;
	//Polygon poly2(p3, l1);
	//Polygon poly = poly2;

	std::cout << p1 << '\n';
	std::cout << l1 << '\n';
	std::cout << poly << '\n';


	system("pause");
	return 0;
}