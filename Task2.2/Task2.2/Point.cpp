#include "Point.h"

//Private:

//This library only allows for 2D and 3D points. This method enforces this restriction.
void Point::restrainNrOfAxis()
{
	if (m_nrOfAxis < 2 || m_nrOfAxis > 3) // Restrain to 2 or 3 axis.
		throw std::runtime_error("This library only allows for 2D and 3D.");
}

//Public:

void Point::set(int x, int y) //Sets point to 2D point.
{
	m_coords.clear(); // Clears m_coords, this will reset the point.
	m_coords.push_back(x);
	m_coords.push_back(y);
	m_nrOfAxis = m_coords.size(); //Sets nrOfAxis, to m_coords.size(). In this case, the axis will be 2. No need to run restrainNrOfAxis-method.
	m_unset = false; //Point is set.
}

void Point::set(int x, int y, int z) // Same as above, but will be set to a 3D point instead.
{
	m_coords.clear();
	m_coords.push_back(x);
	m_coords.push_back(y);
	m_coords.push_back(z);
	m_nrOfAxis = m_coords.size();
	m_unset = false;
}

void Point::set(const std::vector<int> &coords)
{
	m_coords = coords;
	m_nrOfAxis = m_coords.size(); //Set nrOfAxis to size of coords. Since each element of coords reprisent an axis, this should be correct.
	restrainNrOfAxis(); //Vector sent in can be of any size. If user passed in something other than 2D or 3D, exception is called. 
	m_unset = false;
}

bool Point::isAxisCompatible(const Point &other_point) const //Checks if this point has the same amount of axis as other_point.
{
	if (m_nrOfAxis == other_point.m_nrOfAxis)
		return true;
	return false;
}

bool Point::operator==(const Point &other_point) const
{
	for (unsigned int i = 0; i < m_nrOfAxis; i++)
	{
		if (m_coords[i] != other_point.m_coords[i])
			return false; //If any of the coordinates do not match, the points are different, and false can be returned.
	}
	return true; // At this point, all coorinates are equal, and the point are also equal. True can be returned.
}

bool Point::operator!=(const Point & other_point) const
{
	return !(operator==(other_point)); //Simply the opposite of the == operator.
}

std::istream &operator>>(std::istream &is, Point &point) //The >> operator expects this format for points: (x,y) or (x,y,z)
{
	//Check if the next element in istream is a '('. This means it is a point, and we can read in. Otherwise, just return the istream as is.
	if (is.peek() == '(')
	{
		point.m_coords.clear(); //Resets the m_coords. This makes the vector empty.
		int i; // int to be inserted into the point.
		char c; // char to read in the symbols between the numbers, such as '(' ',' ')' and more.
		is >> c; // Clears out '('.
		while (c != ')') //Keep reading until the end of point symbol ')' is found.
		{
			is >> i; 
			point.m_coords.push_back(i);
			is >> c;
		}
		point.m_nrOfAxis = point.m_coords.size(); //Sets the nrOfAxis to the size of coords.
		point.restrainNrOfAxis(); //Must also restrain, in case user enters a dimension other than 2D or 3D.
		point.m_unset = false; // Point is set. Unset points, can also use the >> operator.
	}
	return is;
}

std::ostream& operator<<(std::ostream &s, const Point& point) //Outputs the point in a format like this: (x,y) for 2D, and (x,y,z) for 3D.
{ 
	s << '(';
	for (unsigned int i = 0; i < point.nrOfAxis() - 1; i++) //For all coords, except the last one.
	{
		s << point.m_coords[i] << ',';
	}
	s << point.m_coords[point.nrOfAxis() - 1]; // The last elements is outside the loop, so that it will not be followed by a comma.
	s << ')';

	return s;
}