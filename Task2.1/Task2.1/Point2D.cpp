#include "Point2D.h"

Point2D::Point2D(){}

Point2D::Point2D(const Coord2D & coords)
{
	m_coords = coords;
}

Point2D::Point2D(int _x, int _y) : Point2D(Coord2D(_x, _y)){}

void Point2D::set(const Coord2D & coords)
{
	m_coords = coords;
}

Coord2D & Point2D::get()
{
	return m_coords;
}

unsigned int Point2D::distanceBetweenPoints(Point2D & other_point)
{
	return (sqrt(pow(get().x - other_point.get().x, 2) + pow(get().y - other_point.get().y, 2)));
}
