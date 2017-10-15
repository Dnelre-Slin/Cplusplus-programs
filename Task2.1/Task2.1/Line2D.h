#pragma once
#include "Coord.h"
#include "Point2D.h"

class Line2D
{
private:
	Point2D m_points[2];
public:
	Line2D();
	Line2D(const Coord2D &start_point, const Coord2D &end_point);
	Line2D(const Point2D &start_point, const Point2D &end_point);

	void set(const Coord2D &start_point, const Coord2D &end_point);
	void set(const Point2D &start_point, const Point2D &end_point);

	Point2D &operator[](int index);
	Point2D &get(int index);

	unsigned int closestPoint(Point2D &other_point);
};