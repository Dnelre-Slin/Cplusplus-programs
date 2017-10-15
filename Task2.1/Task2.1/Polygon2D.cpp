#include "Polygon2D.h"

void Polygon2D::incSize()
{
	m_size++;
	if (m_size > m_max_size)
		resizeArray();
}

void Polygon2D::resizeArray()
{
	unsigned int old_max = m_max_size;
	m_max_size *= 2;

	Line2D *temp_array = new Line2D[m_max_size];

	for (unsigned int i = 0; i < old_max; i++)
	{
		temp_array[i] = m_lines[i];
	}

	delete[] m_lines;
	m_lines = temp_array;
}

Line2D &Polygon2D::getClosestLine(Point2D &point)
{
	unsigned int closest_index = 0;
	for (unsigned int i = 1; i < m_size; i++)
	{
		if (m_lines[i].closestPoint(point) < m_lines[closest_index].closestPoint(point))
			closest_index = i;
	}
	return m_lines[closest_index];
}

Polygon2D::Polygon2D()
{
	m_max_size = 10;
	m_lines = new Line2D[m_max_size];
	m_size = 0;
}

Polygon2D::Polygon2D(Point2D &point, Line2D &line)
{
	m_max_size = 10;
	m_lines = new Line2D[m_max_size];
	m_size = 3;

	m_lines[0] = line;
	m_lines[1] = Line2D(line[1], point.get());
	m_lines[2] = Line2D(point.get(), line[0]);
}

Polygon2D::Polygon2D(Point2D &point1, Point2D &point2, Point2D &point3) : Polygon2D(point1, Line2D(point2,point3)){}

Polygon2D::Polygon2D(const Polygon2D &polygon)
{
	m_max_size = polygon.m_max_size;
	m_size = polygon.m_size;
	for (unsigned int i = 0; i < m_size; i++)
	{
		m_lines[i] = polygon.m_lines[i];
	}
}

Polygon2D &Polygon2D::operator=(const Polygon2D &polygon)
{
	m_max_size = polygon.m_max_size;
	m_size = polygon.m_size;
	for (unsigned int i = 0; i < m_size; i++)
	{
		m_lines[i] = polygon.m_lines[i];
	}
	return *this;
}

Polygon2D::~Polygon2D()
{
	delete[] m_lines;
}

Line2D &Polygon2D::operator[](int index)
{
	return m_lines[index];
}

Polygon2D &Polygon2D::operator+=(Point2D &point)
{
	incSize();
	Line2D &line = getClosestLine(point);
	Point2D  temp_point = line[1];
	line[1] = point;
	m_lines[m_size - 1] = Line2D(temp_point, point);
	return *this;
}

unsigned int Polygon2D::size()
{
	return m_size;
}
