#include "Polygon.h"

// Private:
void Polygon::incSize(unsigned int inc_by) // Used to increase size of polygon. Will automatically resize when necessary.
{
	m_size += inc_by; // m_size should not be increased directly in any other methods, only be this method, except for in the set functions, when memory_size is set as well.
	if (m_size > m_max_size)
		resize(); // Will resize when m_size is bigger than current max_size.
}

void Polygon::resize() //Resizes the array size.
{
	unsigned int new_max = m_size * 2; // The new array should be twice the size of the current one.
	Point *temp_arr = new Point[new_max]; //Makes new array on heap, temp_arr is currently pointing at it.

	for (unsigned int i = 0; i < m_max_size; i++)
	{
		temp_arr[i] = m_points[i]; // Copy the elements of m_points into the first half of the new temp_arr.
	}

	delete[] m_points; //Deallocate the memory of the original array.
	m_points = temp_arr; // Make m_points point to the new array.
	m_max_size = new_max; //Set max_size to the new max size.
}

bool Polygon::checkIfPointAlreadyInPolygon(const Point &point) const //Check if this point is already in the polygon.
{
	for (unsigned int i = 0; i < m_size; i++)
	{
		if (point == m_points[i])
			return true; //return true as soon as an equal point is found.
	}
	return false; //Point has no equal. False can be returned.
}

void Polygon::checkAxisCompatibility(const Point &point) const // Check if point is of different dimensions than the polygon. Throw an exception if so.
{
	if (point.nrOfAxis() != m_nrOfAxis)
		throw std::runtime_error("Can not combine polygons, lines or points with different number of axis.");
}

// Public:

Polygon::Polygon(unsigned int nrOfAxis) //Default constructor must specify nrOfAxis. This is so that when += is used on this polygon, it will know whether it is legal or not.
{
	m_size = 0; // Size is 0, as no points have yet been specifide.
	m_max_size = 10; //Max_size set to 10. Will need to resize when size gets bigger than this.
	m_nrOfAxis = nrOfAxis;
	m_points = new Point[m_max_size]; //Allocate an array of ten elements.
}
Polygon::Polygon(const Polygon &polygon)
{
	m_points = 0; // Set to zero, so that the delete in the assignment operator should not cause problems.
	*this = polygon; // Use assignment operator.
}
Polygon::Polygon(Polygon && polygon)
{
	m_points = 0; // Set to zero because delete is called in move assignment operator.
	*this = std::move(polygon); // Use move assignment operator.
}
Polygon::Polygon(const Point &point1, const Point &point2, const Point &point3) //This and all following constructor use their respective set methods.
{
	m_points = 0;
	set(point1, point2, point3);
}
Polygon::Polygon(const Point &point, const Line &line)
{
	m_points = 0;
	set(point, line);
}
Polygon::Polygon(const Line & line1, const Line & line2)
{
	m_points = 0;
	set(line1, line2);
}
Polygon::Polygon(const Point &point, const Polygon &polygon)
{
	m_points = 0;
	set(point, polygon);
}
Polygon::Polygon(const Line &line, const Polygon &polygon)
{
	m_points = 0;
	set(line, polygon);
}
Polygon::Polygon(const Polygon &polygon1, const Polygon &polygon2)
{
	m_points = 0;
	set(polygon1, polygon2);
}

Polygon &Polygon::operator=(const Polygon &polygon)
{
	delete[] m_points; // Delete current array.
	m_max_size = polygon.m_max_size; //Copy all values.
	m_size = polygon.m_size;
	m_nrOfAxis = polygon.m_nrOfAxis;

	m_points = new Point[m_max_size];
	for (unsigned int i = 0; i < m_size; i++) //Deep copy the elements stored on heap.
	{
		m_points[i] = polygon.m_points[i];
	}
	return *this;
}

Polygon &Polygon::operator=(Polygon &&polygon)
{
	delete[] m_points; // Delete current array.

	m_max_size = std::move(polygon.m_max_size); //Move all values.
	m_size = std::move(polygon.m_size);
	m_nrOfAxis = std::move(polygon.m_nrOfAxis);
	m_points = std::move(polygon.m_points); //Simply move the pointer address. Data on heap will not be moved or copied.

	polygon.m_points = 0; // Sets the other polygons m_points pointer to 0, so that it will not try to delete, or use the array, which was moved to this polygon.
	return *this;
}

void Polygon::set(const Polygon &polygon)
{
	operator=(polygon); // Use assignment operator.
}
void Polygon::set(const Point &point, const Line &line) // Makes polygon from point and line.
{
	delete[] m_points; //Delete current array.
	m_size = 0; //m_size will be increased further down.
	m_max_size = 10;
	m_nrOfAxis = point.nrOfAxis();

	if (point == line.get(0) || point == line.get(1)) //Check if any points are similar.
		throw std::runtime_error("Polygon can not consist of two or more similar points.");
	checkAxisCompatibility(line[0]); //And check if they are all of the same dimension.

	m_points = new Point[m_max_size]; // Allocate place for a new array.
	m_points[m_size++] = point; //Put point and points in line into m_points array.
	m_points[m_size++] = line[0]; //m_size can be increased directly, since we know that size will end up as 3, and max_size is 10.
	m_points[m_size++] = line[1];
}
void Polygon::set(const Line &line1, const Line &line2) //The rest of the set-methods, use their respective + or += operators.
{
	*this = line1[0] + line2;
	*this += line1[1];
}
void Polygon::set(const Point &point1, const Point &point2, const Point &point3)
{
	*this = point1 + (point2 + point3);
}
void Polygon::set(const Point &point, const Polygon &polygon)
{
	*this = polygon + point;
}
void Polygon::set(const Line &line, const Polygon &polygon)
{
	*this = polygon + line;
}
void Polygon::set(const Polygon &polygon1, const Polygon &polygon2)
{
	*this = polygon1 + polygon2;
}

bool Polygon::operator==(const Polygon & other) const // Check if two polygons are equal.
{
	for (unsigned int i = 0; i < m_size; i++) //Note that two polygons could consist of the exact same points, and still not be equal. 
	{										  //Points must be equal at the same index, for two polygons to be considered equal.
		if (m_points[i] != other.m_points[i])
			return false;
	}
	return true;
}

Polygon &Polygon::operator+=(const Point &point) //Add point to polygon.
{
	checkAxisCompatibility(point); //Check if point is of same dimension as polygon.
	if (!checkIfPointAlreadyInPolygon(point)) //Only add point, if it is not already in polygon.
	{
		incSize(1); //Use safe increase of size.
		m_points[m_size - 1] = point; //Add point to last place in array. This will not be the actual last place of the array, since array is set to max_size and not size.
	}
	return *this;
}
Polygon Polygon::operator+(const Point &point) const
{
	return Polygon(*this) += point; //Make a copy of this polygon, and use the += operator on it, then return it.
}

Polygon &Polygon::operator+=(const Line &line) //Add line to polygon.
{
	checkAxisCompatibility(line[0]); //Only need to check if one of the points in line, is axis compatible, since both points in line must be of same axis nr.
	//Individually add each point in line, if it is not already in polygon.
	if (!checkIfPointAlreadyInPolygon(line.get(0)))
	{
		incSize(1);
		m_points[m_size - 1] = line.get(0);
	}

	if (!checkIfPointAlreadyInPolygon(line.get(1)))
	{
		incSize(1);
		m_points[m_size - 1] = line.get(1);
	}

	return *this;
}
Polygon Polygon::operator+(const Line &line) const
{
	return Polygon(*this) += line; //Use += operator on copy.
}

Polygon &Polygon::operator+=(const Polygon &polygon) //Add polygon to polygon.
{
	if (m_nrOfAxis != polygon.m_nrOfAxis) //Check if polygons are of same dimension.
		throw std::runtime_error("Can not combine polygons with different number of axis.");
	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		if (!checkIfPointAlreadyInPolygon(polygon.get(i))) //Only add the points that are not already in this polygon.
		{
			incSize(1);
			m_points[m_size - 1] = polygon.get(i);
		}
	}

	return *this;
}
Polygon Polygon::operator+(const Polygon &polygon) const
{
	return Polygon(*this) += polygon; //User += operator on copy.
}

Polygon operator+(const Point &point, const Polygon &polygon) //Rest of + opeartors use another + operator or a constructor.
{
	return polygon + point;
}
Polygon operator+(const Line &line, const Polygon &polygon)
{
	return polygon + line;
}

Polygon operator+(const Point &point, const Line &line)
{
	return Polygon(point, line);
}
Polygon operator+(const Line &line, const Point &point)
{
	return point + line;
}

Polygon operator+(const Line &line1, const Line &line2)
{
	return Polygon(line1, line2);
}

std::istream &operator>>(std::istream &is, Polygon &polygon) // The >> operator expects the followin syntax for polygons: {(point),(point),...,(point)}
{
	// Only read in, if the next element is '{'.
	if (is.peek() == '{')
	{
		char c;
		is >> c; // Clear out '{'.

		//Take for first point first, to get the number of axis the point has.
		Point point0;
		is >> point0;
		Polygon poly(point0.nrOfAxis()); // Initiate polygon with the same number of axis as the first point.
		poly += point0;

		is >> c;
		while (c != '}') //Get the rest of the points. If some of them have a different number of axis, exception will be thrown.
		{
			Point point;
			is >> point;
			poly += point;
			is >> c; //c should become ',' or '}'. If it is '}', while-loop will end.
		}
		polygon = std::move(poly); // Move poly to polygon. Use move assignment operator, to possibly save resources.
	}
	return is;
}

std::ostream &operator<<(std::ostream &s, const Polygon &polygon) //Outputs polygon in the following format: {(point),(point),...,(point)}
{
	s << '{';
	for (unsigned int i = 0; i < polygon.size() - 1; i++) //For-loop through each point in polygon, except for the last one.
	{
		s << polygon.get(i) << ',';
	}
	s << polygon.get(polygon.size() - 1); //Last  point outside of loop, to avoid comma behind it.
	s << '}';
	return s;
}