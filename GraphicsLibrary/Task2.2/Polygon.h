#pragma once
#include <iostream>
#include "Line.h"
#include "Point.h"

class Polygon
{
private:
	unsigned int m_size, m_max_size;
	Point *m_points;
	unsigned int m_nrOfAxis;

	void incSize(unsigned int inc_by);
	void resize();
	bool checkIfPointAlreadyInPolygon(const Point &point) const;
	void checkAxisCompatibility(const Point &point) const;
public:
	Polygon(unsigned int nrOfAxis);
	Polygon(const Polygon &polygon); //Copy constructor.
	Polygon(Polygon &&polygon); //Move constructor.
	Polygon(const Point &point, const Line &line);
	Polygon(const Line &line1, const Line &line2);
	Polygon(const Point &point1, const Point &point2, const Point &point3);
	Polygon(const Point &point, const Polygon &polygon);
	Polygon(const Line &line, const Polygon &polygon);
	Polygon(const Polygon &polygon1, const Polygon &polygon2);

	inline ~Polygon() { delete[] m_points; }

	Polygon &operator=(const Polygon &polygon); // Assignment operator.
	Polygon &operator=(Polygon &&polygon); // Move assignment operator.

	void set(const Polygon &polygon);
	void set(const Point &point1, const Point &point2, const Point &point3);
	void set(const Point &point, const Line &line);
	void set(const Line &line1, const Line &line2);
	void set(const Point &point, const Polygon &polygon);
	void set(const Line &line, const Polygon &polygon);
	void set(const Polygon &polygon1, const Polygon &polygon2);

	inline const Point &get(unsigned int index) const { return m_points[index]; } //Vector class handles out of bounds exceptions.
	inline Point &operator[](unsigned int index) { return m_points[index]; } //Vector class handles out of bounds exceptions.
	inline unsigned int size() const { return m_size; }

	bool operator==(const Polygon &other) const;

	Polygon &operator+=(const Point &point);
	Polygon operator+(const Point &point) const;
	Polygon &operator+=(const Line &line);
	Polygon operator+(const Line &line) const;
	Polygon &operator+=(const Polygon &polygon);
	Polygon operator+(const Polygon &polygon) const;


	friend Polygon operator+(const Point &point, const Polygon &polygon);
	friend Polygon operator+(const Line &line, const Polygon &polygon);
	friend Polygon operator+(const Point &point, const Line &line);
	friend Polygon operator+(const Line &line, const Point &point);
	friend Polygon operator+(const Line &line1, const Line &line2);

	friend std::istream &operator>>(std::istream &is, Polygon &polygon);
	friend std::ostream &operator<<(std::ostream &os, const Polygon &polygon);

};