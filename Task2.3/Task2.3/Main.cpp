#include <iostream>
#include <string>
#include "Point2D.h"

int main()
{
	Point *pp;

	pp = new Point2D;

	Coords *co;

	co = new Coords3D;

	//Point2D p;

	pp->set(Coords2D(1, 2));

	//std::cout << *pp << '\n';

	//std::cout << pp->get().test() << '\n';

	std::cout << (*co).i << '\n';

	delete co;
	delete pp;

	system("PAUSE");
	return 0;
}