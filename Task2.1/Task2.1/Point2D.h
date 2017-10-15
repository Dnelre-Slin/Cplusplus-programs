#pragma once
#include "Coord.h"
#include <iostream>

class Point2D
{
private:
	Coord2D m_coords;
public:
	Point2D();
	Point2D(const Coord2D &coords);
	Point2D(int _x, int _y);

	void set(const Coord2D &coords);
	Coord2D &get();

	unsigned int distanceBetweenPoints(Point2D &other_point);
};