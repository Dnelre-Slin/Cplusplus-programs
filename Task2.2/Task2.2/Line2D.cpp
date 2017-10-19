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

