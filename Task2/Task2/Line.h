#pragma once
#include <iostream>
#include "Point.h"

class Line
{
private:
	Point m_line_coords[2];
public:
	Line();
	Line(int start_x, int start_y, int end_x, int end_y);
	Line(int point_coords[4]);
	Line(Point line_coords[2]);
	Line(const Point &start_of_line, const Point &end_of_line);
	Line(const Line &l);

	Point &operator[](int index);

	friend Line operator+(const Point &point1, const Point &point2);

	friend std::ostream &operator<<(std::ostream &s, const Line &l);
};