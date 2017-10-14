#include "Point.h"

Point::Point()
{
}

Point::Point(int x, int y)
{
	m_x = x;
	m_y = y;
}

std::ostream &operator<<(std::ostream &s, const Point &p)
{
	s << '(' << p.m_x << ',' << p.m_y << ')';
	return s;
}
