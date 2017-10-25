#pragma once
#include <iostream>
#include "Point2D.h"

class Line2D
{
private:
	Point2D m_points[2];
public:
	Line2D();
	Line2D(const Point2D &point1, const Point2D &point2);

	void set(const Point2D &point1, const Point2D &point2);
	const Point2D &get(int index) const;

	Point2D &operator[](int index);
	Point2D &at(int index);

	double getLineLength() const;
	const Point2D &getOtherPoint(const Point2D &point) const;
	friend Line2D operator+(const Point2D &point1, const Point2D &point2);
	friend std::ostream &operator<<(std::ostream &os, const Line2D &line);
};