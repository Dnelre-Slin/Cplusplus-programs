//#include "Polygon2DNew.h"
//
//// Private:
//void Polygon2D::incSize(unsigned int inc_by)
//{
//	m_size += inc_by;
//	if (m_size > m_max_size)
//		resize();
//}
//
//void Polygon2D::resize()
//{
//	unsigned int new_max = m_size * 2;
//	Line2D *temp_arr = new Line2D[new_max];
//
//	for (unsigned int i = 0; i < m_max_size; i++)
//	{
//		temp_arr[i] = m_points[i];
//	}
//
//	delete[] m_points;
//	m_points = temp_arr;
//	m_max_size = new_max;
//}
//
//void Polygon2D::checkClosed() const
//{
//	if (isClosed())
//		throw std::runtime_error("Polygon is closed and cannot be added to.");
//}
//
//Line2D Polygon2D::makeLineBetweenClosestPoints(const Point2D &check_point, const Point2D &option1_point, const Point2D &option2_point) const
//{
//	if (check_point.distanceBetweenPoints(option1_point) < check_point.distanceBetweenPoints(option2_point))
//		return Line2D(check_point, option1_point);
//	else
//		return Line2D(check_point, option2_point);
//}
//
//Line2D Polygon2D::makeLineBetweenClosestPoints(const Line2D &check_line, const Line2D &option_line) const
//{
//	Line2D short_line1 = makeLineBetweenClosestPoints(check_line.get(0), option_line.get(0), option_line.get(0));
//	Line2D short_line2 = makeLineBetweenClosestPoints(check_line.get(1), option_line.get(0), option_line.get(0));
//	if (short_line1.getLineLength() < short_line2.getLineLength())
//		return short_line1;
//	else
//		return short_line2;
//}
//
//
//// Public:
//
//Polygon2D::Polygon2D()
//{
//	m_size = 0;
//	m_max_size = 10;
//	m_is_closed = false;
//	m_points = new Line2D[m_max_size];
//	m_start_point = m_end_point = 0;
//}
//Polygon2D::Polygon2D(const Polygon2D &polygon)
//{
//	m_points = 0;
//	*this = polygon;
//}
//Polygon2D::Polygon2D(const Point2D &point1, const Point2D &point2, const Point2D &point3)
//{
//	m_points = 0;
//	set(point1, point2, point3);
//}
//Polygon2D::Polygon2D(const Point2D &point, const Line2D &line)
//{
//	m_points = 0;
//	set(point, line);
//}
//Polygon2D::Polygon2D(const Point2D &point, const Polygon2D &polygon)
//{
//	m_points = 0;
//	set(point, polygon);
//}
//Polygon2D::Polygon2D(const Line2D &line, const Polygon2D &polygon)
//{
//	m_points = 0;
//	set(line, polygon);
//}
//Polygon2D::Polygon2D(const Polygon2D &polygon1, const Polygon2D &polygon2)
//{
//	m_points = 0;
//	set(polygon1, polygon2);
//}
//
//Polygon2D::~Polygon2D()
//{
//	delete[] m_points;
//}
//
//Polygon2D &Polygon2D::operator=(const Polygon2D &polygon)
//{
//	delete[] m_points;
//	m_max_size = polygon.m_max_size;
//	m_size = polygon.m_size;
//	m_is_closed = polygon.m_is_closed;
//	m_start_point = polygon.m_start_point;
//	m_end_point = polygon.m_end_point;
//
//	m_points = new Line2D[m_max_size];
//	for (unsigned int i = 0; i < m_size; i++)
//	{
//		m_points[i] = polygon.m_points[i];
//	}
//	return *this;
//}
//
//void Polygon2D::set(const Polygon2D &polygon)
//{
//	operator=(polygon);
//}
//void Polygon2D::set(const Point2D &point, const Line2D &line)
//{
//	delete[] m_points;
//	m_size = 0;
//	m_max_size = 10;
//	m_is_closed = false;
//
//	m_points = new Line2D[m_max_size];
//	m_points[m_size++] = makeLineBetweenClosestPoints(point, line.get(0), line.get(1));
//	m_points[m_size++] = line;
//
//	m_start_point = &point;
//	m_end_point = &m_points[m_size - 2].getOtherPoint(point);
//}
//void Polygon2D::set(const Point2D &point1, const Point2D &point2, const Point2D &point3)
//{
//	*this = point1 + (point2 + point3);
//}
//void Polygon2D::set(const Point2D &point, const Polygon2D &polygon)
//{
//	polygon.checkClosed();
//	*this = polygon + point;
//}
//void Polygon2D::set(const Line2D &line, const Polygon2D &polygon)
//{
//	polygon.checkClosed();
//	*this = polygon + line;
//}
//void Polygon2D::set(const Polygon2D &polygon1, const Polygon2D &polygon2)
//{
//	polygon1.checkClosed();
//	polygon2.checkClosed();
//	*this = polygon1 + polygon2;
//}
//
//Polygon2D &Polygon2D::operator+=(const Point2D &point)
//{
//	checkClosed();
//
//	incSize(1);
//	m_points[m_size - 1] = makeLineBetweenClosestPoints(point, *m_start_point, *m_end_point);
//	return *this;
//}
//Polygon2D Polygon2D::operator+(const Point2D &point) const
//{
//	return Polygon2D(*this) += point;
//}
//
//Polygon2D &Polygon2D::operator+=(const Line2D &line)
//{
//	checkClosed();
//
//	incSize(2);
//	m_points[m_size - 2] = makeLineBetweenClosestPoints(line, Line2D(*m_start_point, *m_end_point));
//	m_points[m_size - 1] = line;
//	return *this;
//}
//Polygon2D Polygon2D::operator+(const Line2D &line) const
//{
//	return Polygon2D(*this) += line;
//}
//
//Polygon2D &Polygon2D::operator+=(const Polygon2D &polygon)
//{
//	checkClosed();
//
//	unsigned int old_size = m_size;
//	incSize(polygon.size());
//
//	for (unsigned int i = 0; i < polygon.size(); i++)
//	{
//		m_points[i + old_size] = polygon.get(i);
//	}
//	
//	return *this;
//}
//Polygon2D Polygon2D::operator+(const Polygon2D &polygon) const
//{
//	return Polygon2D(*this) += polygon;
//}
//
//
//Polygon2D operator+(const Point2D &point, const Polygon2D &polygon)
//{
//	return polygon + point;
//}
//Polygon2D operator+(const Line2D &line, const Polygon2D &polygon)
//{
//	return polygon + line;
//}
//
//Polygon2D operator+(const Point2D &point, const Line2D &line)
//{
//	return Polygon2D(point, line);
//}
//Polygon2D operator+(const Line2D &line, const Point2D &point)
//{
//	return point + line;
//}
//
//std::ostream &operator<<(std::ostream &s, const Polygon2D &polygon)
//{
//	s << '{';
//	for (unsigned int i = 0; i < polygon.size() - 1; i++)
//	{
//		s << polygon.get(i) << ',';
//	}
//	s << polygon.get(polygon.size() - 1);
//	s << '}';
//	return s;
//}