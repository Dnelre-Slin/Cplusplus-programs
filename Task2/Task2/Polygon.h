#pragma once
#include <iostream>
#include "Line.h"

class Polygon
{
private:
	Line m_polygon_coords[5];
	int m_size, m_max_size;
public:
	Polygon();
	Polygon(const Point &p, Line &l);
	Polygon(const Polygon &poly);

	Line &operator[](int index);

	friend Polygon operator+(Point &p, Line &l);
	friend Polygon operator+(Line &l, Point &p);

	friend std::ostream &operator<<(std::ostream &s, const Polygon &poly);
};