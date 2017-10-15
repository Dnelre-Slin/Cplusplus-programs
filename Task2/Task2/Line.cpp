#include "Line.h"

Line::Line()
{
}

Line::Line(int start_x, int start_y, int end_x, int end_y)
{
	m_line_coords[0] = Point(start_x, start_y);
	m_line_coords[1] = Point(end_x, end_y);
}

Line::Line(int point_coords[4]) : Line(point_coords[0], point_coords[1], point_coords[2], point_coords[3]){}

Line::Line(Point line_coords[2])
{
	m_line_coords[0] = Point(line_coords[0]);
	m_line_coords[1] = Point(line_coords[1]);
}

Line::Line(const Point &start_of_line, const Point &end_of_line)
{
	m_line_coords[0] = start_of_line;
	m_line_coords[1] = end_of_line;
}

Line::Line(const Line & l)
{
	m_line_coords[0] = l.m_line_coords[0];
	m_line_coords[1] = l.m_line_coords[1];
}

Point &Line::operator[](int index)
{
	return m_line_coords[index];
}

Line operator+(const Point &point1, const Point &point2)
{
	return Line(point1, point2);
}

std::ostream &operator<<(std::ostream &s, const Line &l)
{
	s << '[';
	s << l.m_line_coords[0] << ',' << l.m_line_coords[1];
	s << ']';
	return s;
}
