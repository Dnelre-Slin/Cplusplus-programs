#include "Point2D.h"

Point2D::Point2D(){}
Point2D::Point2D(int x, int y) : m_coords(x,y) {}
Point2D::Point2D(const Coord2D &coords) : m_coords(coords) {}

void Point2D::set(int x, int y)
{
	m_coords.x = x;
	m_coords.y = y;
}

void Point2D::set(const Coord2D &coords)
{
	m_coords.x = coords.x;
	m_coords.y = coords.y;
}

const Coord2D &Point2D::get() const //Use this method when object is used in const context.
{
	return m_coords;
}

Coord2D &Point2D::at() //Get reference to coords.
{
	return m_coords;
}

std::ostream& operator<<(std::ostream &s, const Point2D& point)
{
	s << '(' << point.get().x << ',' << point.get().y << ')';
	return s;
}