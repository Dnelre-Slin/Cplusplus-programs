#pragma once
#include <iostream>
#include "Point.h"

class Line
{
private:
	Point m_points[2];
	unsigned int m_nrOfAxis;
	bool m_unset;
public:
	inline Line() { m_unset = true; } //Line is unset, and unsafe to use.
	inline Line(const Point &point1, const Point &point2) { set(point1, point2); }

	void set(const Point &point1, const Point &point2);
	
	inline const Point &operator[](int index) const { return m_points[index]; }
	inline const Point &get(int index) const { return operator[](index); }

	inline bool unset() { return m_unset; } // Return whether line is unset. If so, it is unsafe to use.

	bool operator==(const Line &other) const;

	friend Line operator+(const Point &point1, const Point &point2);

	friend std::istream &operator>>(std::istream &is, Line &line);
	friend std::ostream &operator<<(std::ostream &os, const Line &line);
};