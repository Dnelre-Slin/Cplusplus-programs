#pragma once

#include "Point.h"

class Point2D : public Point
{
private:
	Coords2D m_coords;
public:
	Point2D(){}
	Point2D(const Coords2D &coords) : m_coords(coords){}

	inline void set(const Coords2D &coords) { m_coords = coords; }
	inline const Coords2D &get() const { return m_coords; }
	inline Coords2D &at() { return m_coords; }

	inline friend std::ostream &operator<<(std::ostream &os, const Point2D &point)
	{
		return os << '(' << point.m_coords.x << ',' << point.m_coords.y << ')';
	}
};