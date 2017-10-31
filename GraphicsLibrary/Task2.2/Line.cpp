#include "Line.h"

// Public:

void Line::set(const Point &point1, const Point &point2) //Sets line.
{
	if (point1 == point2) //If both points are the same, the line would tecnically be a point. This should not be allowed, so an exception is thrown.
		throw std::runtime_error("Line must consist of two different points");
	if (!point1.isAxisCompatible(point2)) // If the to points are of two different dimensions, an exception will be thrown, as this points would be incompatible.
		throw std::runtime_error("Can not combine points with different number of axis.");
	m_points[0] = point1;
	m_points[1] = point2;
	m_nrOfAxis = point1.nrOfAxis(); // Sets nrOfAxis for the line, to be the same as one of the points nrOfAxis. Does not matter which point, as both points must have the same nrOfAxis.
	m_unset = false; // Line is no longer unset, and can be used safely.
}

inline Point &Line::operator[](int index) //Get referance to points. Can modify points outside class using this method.
{
	if (m_unset) // Must be set.
		throw std::runtime_error("Cannot modify unset line.");
	if (index < 2) // Limit to two points. Anything else is out of bounds.
		return m_points[index];
	throw std::runtime_error("Index out of bounds.");
}

inline const Point & Line::get(int index) const // Same as above, but can be used by const objets. Obviously cannot modify points using this const method.
{
	//Can be used when unset, but not safe.
	if (index < 2)
		return m_points[index];
	throw std::runtime_error("Index out of bounds.");
}

bool Line::operator==(const Line &other) const
{
	if (m_points[0] == other.m_points[0] && m_points[1] == other.m_points[1]) // If first points and second points are equal, line is equal.
		return true; // Note that these lines: [(1,2),(3,4)] and [(3,4),(1,2)], would not be considered equal by this method. 
	return false;
}

Line operator+(const Point &point1, const Point &point2) // Add two points, and get a line.
{
	return Line(point1, point2); //Uses the constructor, which again uses the set method. All error checking is done in the set method.
}

std::istream &operator>>(std::istream &is, Line &line) //The >> operator expects this format for lines: [(x,y),(x,y)] or [(x,y,z),(x,y,z)]
{
	// Just as in point. Only read in, if the next element in istream is a '['.
	if (is.peek() == '[')
	{
		Line new_line;
		is.get(); // Clear out the '['.
		is >> new_line.m_points[0]; // Uses points overloaded >> operator.
		is.get(); // Clear out the ','.
		is >> new_line.m_points[1];
		is.get(); // Clear out the ']'.

		if (!new_line.m_points[0].isAxisCompatible(new_line.m_points[1])) // Makes sure that both points in lines have the same amount of dimensions.
			throw std::runtime_error("Can not combine points with different number of axis.");
		line = std::move(new_line); //Use the move assignment operator, since new_line will not be used passed this point. Could save some resources.
		line.m_nrOfAxis = line.m_points[0].nrOfAxis();
		line.m_unset = false; // Line is now set. Unset lines could also use the >> operator.
	}
	return is;
}

std::ostream &operator<<(std::ostream &s, const Line &line) //Outputs lines in this format: [(x,y),(x,y)] or [(x,y,z),(x,y,z)].
{
	s << '[' << line.get(0) << ',' << line.get(1) << ']';
	return s;
}