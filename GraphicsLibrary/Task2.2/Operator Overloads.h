//#pragma once
//#include "Polygon2D.h"
//
//// Point overloads
//
//std::ostream& operator<<(std::ostream &s, const Point2D& point)
//{
//	s << '(' << point.get().x << ',' << point.get().y << ')';
//	return s;
//}
//
//// End of Point
//
//// Line overloads
//
//Line2D operator+(const Point2D &point1, const Point2D &point2)
//{
//	return Line2D(point1, point2);
//}
//
//std::ostream& operator<<(std::ostream& s, const Line2D& line)
//{
//	s << '[' << line.get(0) << ',' << line.get(1) << ']';
//	return s;
//}
//
//// End of Line
//
//// Polygon overloads
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
//Polygon2D operator+(const Point2D &point, const Polygon2D &polygon)
//{
//	return Polygon2D(point, polygon);
//}
//Polygon2D operator+(const Polygon2D &polygon, const Point2D &point)
//{
//	return point + polygon;
//}
//
//Polygon2D operator+(const Line2D &line, const Polygon2D &polygon)
//{
//	return Polygon2D(line, polygon);
//}
//Polygon2D operator+(const Polygon2D &polygon, const Line2D &line)
//{
//	return line + polygon;
//}
//
//Polygon2D operator+(const Polygon2D &polygon1, const Polygon2D &polygon2)
//{
//	return Polygon2D(polygon1, polygon2);
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
//
//// End of Polygon