#include "Polygon.h"

Polygon::Polygon()
{
}

Polygon::Polygon(const Point &p, Line &l)
{
	m_size = 3;
	m_max_size = 5;

	m_polygon_coords[0] = l;
	m_polygon_coords[1] = Line(l[1], p);
	m_polygon_coords[2] = Line(p, l[0]);
}

Polygon::Polygon(const Polygon &poly)
{
	m_size = poly.m_size;
	m_max_size = poly.m_max_size;

	m_polygon_coords[0] = poly.m_polygon_coords[0];
	m_polygon_coords[1] = poly.m_polygon_coords[1];
	m_polygon_coords[2] = poly.m_polygon_coords[2];
}

Line & Polygon::operator[](int index)
{
	return m_polygon_coords[index];
}

Polygon operator+(Point &p, Line &l)
{
	return Polygon(p, l);
}

Polygon operator+(Line &l, Point &p)
{
	return p + l;
}

std::ostream & operator<<(std::ostream &s, const Polygon &poly)
{
	s << '{';
	for (int i = 0; i < poly.m_size - 1; i++)
	{
		s << poly.m_polygon_coords[i] << ',';
	}
	s << poly.m_polygon_coords[poly.m_size-1];
	s << '}';
	return s;
}
