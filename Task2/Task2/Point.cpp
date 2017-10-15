#include "Point.h"

Point::Point()
{
}

Point::Point(int x, int y)
{
	m_coords[0] = x;
	m_coords[1] = y;
}

Point::Point(int coords[2])
{
	m_coords[0] = coords[0];
	m_coords[1] = coords[1];
}

Point::Point(const Point & p)
{
	m_coords[0] = p.m_coords[0];
	m_coords[1] = p.m_coords[1];
}

Point &Point::operator=(const Point & p)
{
	m_coords[0] = p.m_coords[0];
	m_coords[1] = p.m_coords[1];
	return *this;
}

int &Point::operator[](int index)
{
	return m_coords[index];
}

std::ostream &operator<<(std::ostream &s, const Point &p)
{
	s << '(' << p.m_coords[0] << ',' << p.m_coords[1] << ')';
	return s;
}
