#include "Line2D.h"

Line2D::Line2D(){}
Line2D::Line2D(const Point2D &point1, const Point2D &point2)
{
	set(point1, point2);
}

void Line2D::set(const Point2D &point1, const Point2D &point2)
{
	m_points[0] = point1;
	m_points[1] = point2;
}

const Point2D &Line2D::get(int index) const
{
	return m_points[index];
}

Point2D & Line2D::operator[](int index)
{
	return m_points[index];
}

Point2D & Line2D::at(int index)
{
	return operator[](index);
}

double Line2D::getLineLength() const
{
	return m_points[0].distanceBetweenPoints(m_points[1]);
}

const Point2D &Line2D::getOtherPoint(const Point2D &point) const
{
	if (point == m_points[0])
		return m_points[1];
	return m_points[0];
}

Line2D operator+(const Point2D &point1, const Point2D &point2)
{
	return Line2D(point1, point2);
}

std::ostream& operator<<(std::ostream& s, const Line2D& line)
{
	s << '[' << line.get(0) << ',' << line.get(1) << ']';
	return s;
}