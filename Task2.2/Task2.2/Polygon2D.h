#pragma once
#include <iostream>
#include "Line2D.h"
#include "Point2D.h"

class Polygon2D
{
private:
	unsigned int m_size, m_max_size;
	Point2D *m_points;
	bool m_is_closed;

	void incSize(unsigned int inc_by);
	void resize();
	void checkClosed() const;
public:
	Polygon2D();
	Polygon2D(const Polygon2D &polygon);
	Polygon2D(const Point2D &point, const Line2D &line);
	Polygon2D(const Point2D &point1, const Point2D &point2, const Point2D &point3);
	Polygon2D(const Point2D &point, const Polygon2D &polygon);
	Polygon2D(const Line2D &line, const Polygon2D &polygon);
	Polygon2D(const Polygon2D &polygon1, const Polygon2D &polygon2);

	virtual ~Polygon2D();

	Polygon2D &operator=(const Polygon2D &polygon);

	void set(const Polygon2D &polygon);
	void set(const Point2D &point1, const Point2D &point2, const Point2D &point3);
	void set(const Point2D &point, const Line2D &line);
	void set(const Point2D &point, const Polygon2D &polygon);
	void set(const Line2D &line, const Polygon2D &polygon);
	void set(const Polygon2D &polygon1, const Polygon2D &polygon2);

	inline const Point2D &get(unsigned int index) const { return m_points[index]; }
	inline Point2D &operator[](unsigned int index) { return m_points[index]; }
	inline Point2D &at(unsigned int index) { return operator[](index); }
	inline unsigned int size() const { return m_size; }
	inline bool isClosed() const { return m_is_closed; }

	Polygon2D &operator+=(const Point2D &point);
	Polygon2D operator+(const Point2D &point) const;
	Polygon2D &operator+=(const Line2D &line);
	Polygon2D operator+(const Line2D &line) const;
	Polygon2D &operator+=(const Polygon2D &polygon);
	Polygon2D operator+(const Polygon2D &polygon) const;


	friend Polygon2D operator+(const Point2D &point, const Polygon2D &polygon);
	friend Polygon2D operator+(const Line2D &line, const Polygon2D &polygon);
	friend Polygon2D operator+(const Point2D &point, const Line2D &line);
	friend Polygon2D operator+(const Line2D &line, const Point2D &point);

	friend std::ostream &operator<<(std::ostream &os, const Polygon2D &polygon);

};