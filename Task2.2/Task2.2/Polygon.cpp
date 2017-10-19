#include "Polygon.h"

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

Polygon2D::Polygon2D(){}
Polygon2D::Polygon2D(const Polygon2D &polygon)
{
	m_max_size = polygon.m_max_size;
	m_size = polygon.m_size;
	m_points = new Point2D[m_max_size];
	for (unsigned int i = 0; i < m_size; i++)
	{
		m_points[i] = polygon.m_points[i];
	}
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
void Polygon2D::set(const Point2D &point1, const Point2D &point2, const Point2D &point3)
{
	delete[] m_points;
	m_size = 3;
	m_max_size = 10;

	m_points = new Point2D[m_max_size];
	m_points[0] = point1;
	m_points[1] = point2;
	m_points[2] = point3;
}
void Polygon2D::set(const Point2D &point, const Line2D &line)
{
	delete[] m_points;
	m_size = 3;
	m_max_size = 10;

	m_points = new Point2D[m_max_size];
	m_points[0] = point;
	m_points[1] = line.get(0);
	m_points[2] = line.get(1);
}
void Polygon2D::set(const Point2D &point, const Polygon2D &polygon)
{
	delete[] m_points;
	m_size = 1 + polygon.size();
	m_max_size = m_size + 10;

	m_points = new Point2D[m_max_size];
	m_points[0] = point;
	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		m_points[i + 1] = polygon.get(i);
	}
}
void Polygon2D::set(const Line2D &line, const Polygon2D &polygon)
{
	delete[] m_points;
	m_size = 2 + polygon.size();
	m_max_size = m_size + 10;

	m_points = new Point2D[m_max_size];
	m_points[0] = line.get(0);
	m_points[1] = line.get(1);
	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		m_points[i + 2] = polygon.get(i);
	}
}
void Polygon2D::set(const Polygon2D &polygon1, const Polygon2D &polygon2)
{
	delete[] m_points;
	m_size = polygon1.size() + polygon2.size();
	m_max_size = m_size + 10;
	m_points = new Point2D[m_max_size];

	for (unsigned int i = 0; i < polygon1.size(); i++)
	{
		m_points[i] = polygon1.get(i);
	}
	for (unsigned int i = 0; i < polygon2.size(); i++)
	{
		m_points[i + polygon1.size()] = polygon2.get(i);
	}
}

const Point2D& Polygon2D::get(unsigned int index) const
{
	return m_points[index];
}

Point2D &Polygon2D::operator[](unsigned int index)
{
	return m_points[index];
}

Point2D &Polygon2D::at(unsigned int index)
{
	return operator[](index);
}

Polygon2D &Polygon2D::operator+=(const Point2D &point)
{
	incSize(1);
	m_points[m_size - 1] = point;
	return *this;
}

Polygon2D &Polygon2D::operator+=(const Line2D &line)
{
	incSize(2);
	m_points[m_size - 2] = line.get(0);
	m_points[m_size - 1] = line.get(1);
	return *this;
}

Polygon2D &Polygon2D::operator+=(const Polygon2D &polygon)
{
	unsigned int old_size = m_size;
	incSize(polygon.size());

	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		m_points[i + old_size] = polygon.get(i);
	}
	
	return *this;
}

unsigned int Polygon2D::size() const
{
	return m_size;
}

