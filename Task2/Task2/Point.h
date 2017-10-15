#pragma once
#include <iostream>

class Point
{
private:
	int m_coords[2];
public:
	Point();
	Point(int x, int y);
	Point(int coords[2]);
	Point(const Point &p);

	Point &operator=(const Point &p);

	int &operator[](int index);

	friend std::ostream &operator<<(std::ostream &s, const Point &p); 
};