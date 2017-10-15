#include "Line2D.h"

Line2D::Line2D(){}

Line2D::Line2D(const Coord2D &start_point, const Coord2D &end_point)
{
	set(start_point, end_point);
}

Line2D::Line2D(const Point2D &start_point, const Point2D &end_point)
{
	set(start_point, end_point);
}

void Line2D::set(const Coord2D &start_point, const Coord2D &end_point)
{
	m_points[0] = start_point;
	m_points[1] = end_point;
}

void Line2D::set(const Point2D &start_point, const Point2D &end_point)
{
	m_points[0] = start_point;
	m_points[1] = end_point;
}

Point2D &Line2D::operator[](int index)
{
	return m_points[index];
}

Point2D & Line2D::get(int index)
{
	return operator[](index);
}

unsigned int Line2D::closestPoint(Point2D & other_point)
{
	if (m_points[0].distanceBetweenPoints(other_point) <= m_points[1].distanceBetweenPoints(other_point))
		return m_points[0].distanceBetweenPoints(other_point);
	else
		return m_points[1].distanceBetweenPoints(other_point);
}
