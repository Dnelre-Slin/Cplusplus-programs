#include "Polygon2D.h"

// Private:
void Polygon2D::incSize(unsigned int inc_by)
{
	m_size += inc_by;
	if (m_size > m_max_size)
		resize();
}

void Polygon2D::resize()
{
	unsigned int new_max = m_size * 2;
	Point2D *temp_arr = new Point2D[new_max];

	for (unsigned int i = 0; i < m_max_size; i++)
	{
		temp_arr[i] = m_points[i];
	}

	delete[] m_points;
	m_points = temp_arr;
	m_max_size = new_max;
}

void Polygon2D::checkClosed() const
{
	if (isClosed())
		throw std::runtime_error("Polygon is closed and cannot be added to.");
}

// Public:

Polygon2D::Polygon2D()
{
	m_size = 0;
	m_max_size = 10;
	m_is_closed = false;
	m_points = new Point2D[m_max_size];
}
Polygon2D::Polygon2D(const Polygon2D &polygon)
{
	m_points = 0;
	*this = polygon;
}
Polygon2D::Polygon2D(const Point2D &point1, const Point2D &point2, const Point2D &point3)
{
	m_points = 0;
	set(point1, point2, point3);
}
Polygon2D::Polygon2D(const Point2D &point, const Line2D &line)
{
	m_points = 0;
	set(point, line);
}
Polygon2D::Polygon2D(const Point2D &point, const Polygon2D &polygon)
{
	m_points = 0;
	set(point, polygon);
}
Polygon2D::Polygon2D(const Line2D &line, const Polygon2D &polygon)
{
	m_points = 0;
	set(line, polygon);
}
Polygon2D::Polygon2D(const Polygon2D &polygon1, const Polygon2D &polygon2)
{
	m_points = 0;
	set(polygon1, polygon2);
}

Polygon2D::~Polygon2D()
{
	delete[] m_points;
}

Polygon2D &Polygon2D::operator=(const Polygon2D &polygon)
{
	delete[] m_points;
	m_max_size = polygon.m_max_size;
	m_size = polygon.m_size;
	m_is_closed = polygon.m_is_closed;
	m_points = new Point2D[m_max_size];
	for (unsigned int i = 0; i < m_size; i++)
	{
		m_points[i] = polygon.m_points[i];
	}
	return *this;
}

void Polygon2D::set(const Polygon2D &polygon)
{
	operator=(polygon);
}
void Polygon2D::set(const Point2D &point, const Line2D &line)
{
	delete[] m_points;
	m_size = 3;
	m_max_size = 10;
	m_is_closed = false;

	m_points = new Point2D[m_max_size];
	m_points[0] = point;
	m_points[1] = line.get(0);
	m_points[2] = line.get(1);
}
void Polygon2D::set(const Point2D &point1, const Point2D &point2, const Point2D &point3)
{
	*this = point1 + (point2 + point3);
}
void Polygon2D::set(const Point2D &point, const Polygon2D &polygon)
{
	polygon.checkClosed();
	*this = polygon + point;
}
void Polygon2D::set(const Line2D &line, const Polygon2D &polygon)
{
	polygon.checkClosed();
	*this = polygon + line;
}
void Polygon2D::set(const Polygon2D &polygon1, const Polygon2D &polygon2)
{
	polygon1.checkClosed();
	polygon2.checkClosed();
	*this = polygon1 + polygon2;
}

Polygon2D &Polygon2D::operator+=(const Point2D &point)
{
	checkClosed();

	incSize(1);
	m_points[m_size - 1] = point;
	return *this;
}
Polygon2D Polygon2D::operator+(const Point2D &point) const
{
	checkClosed();
	return Polygon2D(*this) += point;
}

Polygon2D &Polygon2D::operator+=(const Line2D &line)
{
	checkClosed();

	incSize(2);
	m_points[m_size - 2] = line.get(0);
	m_points[m_size - 1] = line.get(1);
	return *this;
}
Polygon2D Polygon2D::operator+(const Line2D &line) const
{
	checkClosed();
	return Polygon2D(*this) += line;
}

Polygon2D &Polygon2D::operator+=(const Polygon2D &polygon)
{
	checkClosed();

	unsigned int old_size = m_size;
	incSize(polygon.size());

	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		m_points[i + old_size] = polygon.get(i);
	}
	
	return *this;
}
Polygon2D Polygon2D::operator+(const Polygon2D &polygon) const
{
	checkClosed();
	return Polygon2D(*this) += polygon;
}


Polygon2D operator+(const Point2D &point, const Polygon2D &polygon)
{
	polygon.checkClosed();
	return polygon + point;
}
Polygon2D operator+(const Line2D &line, const Polygon2D &polygon)
{
	polygon.checkClosed();
	return polygon + line;
}

Polygon2D operator+(const Point2D &point, const Line2D &line)
{
	return Polygon2D(point, line);
}
Polygon2D operator+(const Line2D &line, const Point2D &point)
{
	return point + line;
}

std::ostream &operator<<(std::ostream &s, const Polygon2D &polygon)
{
	s << '{';
	for (unsigned int i = 0; i < polygon.size() - 1; i++)
	{
		s << polygon.get(i) << ',';
	}
	s << polygon.get(polygon.size() - 1);
	s << '}';
	return s;
}