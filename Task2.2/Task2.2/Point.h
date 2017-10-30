#pragma once
#include <iostream>
#include <vector>

class Point
{
private:
	std::vector<int> m_coords;
	unsigned int m_nrOfAxis;
	bool m_unset;

	void restrainNrOfAxis();
public:
	inline Point() { m_unset = true; } //Set the unset bool to true, this lets users know that the point is not set, and is unsafe to use.
	inline Point(int x, int y) { set(x, y); }
	Point(int x, int y, int z) { set(x, y, z); }
	Point(const std::vector<int> &coords) { set(coords); }

	void set(int x, int y);
	void set(int x, int y, int z);
	void set(const std::vector<int> &coords);
	inline const std::vector<int> &get() const { return m_coords; }

	bool isAxisCompatible(const Point &other_point) const;
	int nrOfAxis() const { return m_nrOfAxis; }

	inline bool unset() { return m_unset; } //Returns whether point is unset. If so, it is not safe to use.

	bool operator==(const Point &other_point) const;
	bool operator!=(const Point &other_point) const;

	friend std::istream &operator>>(std::istream &is, Point &point);
	friend std::ostream &operator<<(std::ostream &os, const Point &point);

};