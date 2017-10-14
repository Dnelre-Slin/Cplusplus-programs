#pragma once
#include <iostream>

class Point
{
private:
	int m_x;
	int m_y;
public:
	Point();
	Point(int x, int y);

	friend std::ostream& operator<<(std::ostream &s, const Point &p); 
};