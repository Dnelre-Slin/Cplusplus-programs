#pragma once
#include <iostream>
#include "Coords.h"

class Point
{
private:
public:
	Point() {};
	Point(const Coords&) {};
	inline virtual void set(const Coords&) {};
	inline virtual const Coords &get() const = 0;
	inline virtual Coords &at() = 0;

	inline friend std::ostream &operator<<(std::ostream &os, const Point &point) { return os; }
};