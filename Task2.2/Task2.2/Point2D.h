#pragma once
#include <iostream>
#include "Coords.h"

class Point2D
{
private:
	Coord2D m_coords;
public:
	Point2D();
	Point2D(int x, int y);
	Point2D(const Coord2D &coords);

	void set(int x, int y);
	void set(const Coord2D &coords);
	const Coord2D &get() const;
	Coord2D &at();

	friend std::ostream &operator<<(std::ostream &os, const Point2D &point);

};