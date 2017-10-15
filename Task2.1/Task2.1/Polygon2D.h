#pragma once
#include "Point2D.h"
#include "Line2D.h"

class Polygon2D
{
private:
	Line2D *m_lines;
	unsigned int m_size, m_max_size;

	void incSize();
	void resizeArray();

	Line2D &getClosestLine(Point2D &point);
public:
	Polygon2D();
	Polygon2D(Point2D &point, Line2D &line);
	Polygon2D(Point2D &point1, Point2D &point2, Point2D &point3);
	Polygon2D(const Polygon2D &polygon);

	Polygon2D &operator=(const Polygon2D &polygon);

	virtual ~Polygon2D();

	Line2D &operator[](int index);

	Polygon2D &operator+=(Point2D &point);

	unsigned int size();
};