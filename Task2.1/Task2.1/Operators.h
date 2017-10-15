#pragma once
#include <iostream>
#include "Coord.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Polygon2D.h"

//Point functions:

std::ostream &operator<<(std::ostream &s, Point2D &point)
{
	s << '(' << point.get().x << ',' << point.get().y << ')';
	return s;
}

//End of Point functions.

//Line functions:

Line2D operator+(const Point2D &point1, const Point2D &point2)
{
	return Line2D(point1, point2);
}

std::ostream &operator<<(std::ostream &s, Line2D &line)
{
	s << '[' << line[0] << ',' << line[1] << ']';
	return s;
}

//End of Line functions.

//Polygon functions:

std::ostream &operator<<(std::ostream &s, Polygon2D &polygon)
{
	s << '{';
	for (unsigned int i = 0; i < polygon.size() - 1; i++)
	{
		s << polygon[i] << ',';
	}
	s << polygon[polygon.size() - 1];
	s << '}';
	return s;
}

//End of Polygon functions.