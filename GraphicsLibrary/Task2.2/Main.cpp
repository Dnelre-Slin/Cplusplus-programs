#include <iostream>
#include <fstream>
#include <time.h>
//#include "Polygon.h"
//#include "Operator Overloads.h"
#include "GraphicsLibrary.h"

// Testing function.
//Get a random point.
Point getRndPoint(unsigned int axis, unsigned int range = 100)
{
	if (axis == 2)
	{
		return Point(rand() % range, rand() % range);
	}
	return Point(rand() % range, rand() % range, rand() % range);
}

//Get a random line.
Line getRndLine(unsigned int axis, unsigned int range = 100)
{
	return Line(getRndPoint(axis, range), getRndPoint(axis, range));
}

//Get a polygon, with a random amount of random points.
Polygon getRndPolygon(unsigned int axis, unsigned int poly_range = 10, unsigned int range = 100)
{
	Polygon poly(axis);
	for (unsigned int i = 0; i < ((rand() % poly_range) + 10); i++)
	{
		poly += getRndPoint(axis, range);
	}
	return poly;
}

//Test to see if the function to restrain points to 2D and 3D works proparly.
void TestPointAxisRestraint()
{
	//Try from 0 to 100 axis. Only 2 and 3 should be allowed.

	bool test_success = true;

	for (unsigned int i = 0; i < 100; i++)
	{
		try
		{
			Point point(std::vector<int>(i, 0)); // Make i number of axis. Set each to 0, as this should not effect the test.
			if (!(i == 2 || i == 3)) //If it reaches this point, and the number of axis is not 2 or 3, test has failed.
				test_success = false;
		}
		catch (std::exception e)
		{
			if (i == 2 && i == 3) // If exception is thrown, when the number of axis is 2 or 3, test has failed.
				test_success = false;
		}
	}

	if (test_success)
		std::cout << "Axis restriction test: Successful.\n";
	else
		std::cout << "Axis restriction test: Failed.\n";
}

// Simple test to see if a randomly made polygon will be made, and printed successfully.
void TestSimplePolygonFunctionality()
{
	unsigned int axis = 2;
	unsigned int size = 20;
	std::vector<Polygon> v2;
	for (unsigned int i = 0; i < size; i++)
	{
		v2.push_back(getRndPolygon(axis));
	}

	for (unsigned int i = 0; i < size; i++)
	{
		std::cout << v2[i] << "   Size: " << v2[i].size() << "\n\n";
	}
}

//Function that checks if a polygon consist of more than one of the same point. Will return true if there are no redundant points.
bool checkRedundantPointInPolygon(const Polygon &polygon)
{
	for (unsigned int i = 0; i < polygon.size(); i++)
	{
		for (unsigned int j = i + 1; j < polygon.size(); j++)
		{
			if (polygon[i] == polygon[j])
			{
				return false;
			}
		}
	}
	return true;
}

//Test to see if several, random polygons will store several of the same point.
void TestPolygonRemoveRedundantPointFunctionality()
{
	unsigned int size = 1000; //Test with a 1000 2D and a 1000 3D polygons.
	std::vector<Polygon> polys2;
	std::vector<Polygon> polys3;
	for (unsigned int i = 0; i < size; i++) 
	{
		polys2.push_back(getRndPolygon(2, 100, 4)); // 100 poly_range, will make each polygon have anywhere from 10 to 110 points.
		polys3.push_back(getRndPolygon(3, 100, 4)); // 4 range, will limit each point to have a coordinate from 0 to 4. High chance of similar points.
	}

	bool b_poly2 = true, b_poly3 = true;

	for (unsigned int i = 0; i < size; i++)
	{
		if (!checkRedundantPointInPolygon(polys2[i]))
			b_poly2 = false; // Failed check. Set to false.
		if (!checkRedundantPointInPolygon(polys3[i]))
			b_poly3 = false;
	}

	// Print results.
	if (b_poly2)
		std::cout << "Poly2: Success.\n";
	else
		std::cout << "Poly2: Failed.\n";
	if (b_poly3)
		std::cout << "Poly3: Success.\n";
	else
		std::cout << "Poly3: Failed.\n";
}

//Check if exception will kick in if trying to add a two axis point, with a three axis one.
void TestAxisMismatchException()
{
	// Two mismatching points.
	try 
	{
		Point point1(getRndPoint(2)); // 2D point.
		Point point2(getRndPoint(3)); // 3D point.
		Line line = point1 + point2; // Should throw exception.
		std::cout << "Failed.\n" << '\n'; // Should not happen.
	}
	catch (std::runtime_error re)
	{
		std::cout << "Success: " << re.what() << '\n';
	}
	// Mismatching line and point.
	try
	{
		Line line(getRndLine(2)); // 2D line.
		Point point(getRndPoint(3)); // 3D point.
		Polygon polygon = line + point; // Should throw exception.
		std::cout << "Failed.\n" << '\n'; // Should not happen.
	}
	catch (std::runtime_error re)
	{
		std::cout << "Success: " << re.what() << '\n';
	}
	// Mismatching line and polygon.
	try
	{
		Line line(getRndLine(3)); // 3D line.
		Polygon polygon1(getRndPolygon(2)); // 2D polygon.
		Polygon polygon2 = line + polygon1; // Should throw exception.
		std::cout << "Failed.\n" << '\n'; // Should not happen.
	}
	catch (std::runtime_error re)
	{
		std::cout << "Success: " << re.what() << '\n';
	}
}

//Function for testing operator overloads.
void TestOperatorOverloads()
{
	Point p1 = getRndPoint(2);
	Point p2 = getRndPoint(2);

	Line l1 = p1 + p2; // Add two points to get line.
	std::cout << "Add two points. Get a line.\n";
	std::cout << p1 << " + " << p2 << " = " << l1 << "\n\n";

	Line l2 = getRndLine(2);

	Polygon poly1 = l1 + l2; // Add to lines to get polygon.
	std::cout << "Add two lines. Get a polygon.\n";
	std::cout << l1 << " + " << l2 << " = " << poly1 << "\n\n";

	Point p3 = getRndPoint(3);
	Line l3 = getRndLine(3);

	Polygon poly2 = p3 + l3; // Add point and line to get polygon.
	std::cout << "Add point and line. Get a polygon.\n";
	std::cout << p3 << " + " << l3 << " = " << poly2 << "\n\n";

	Point p4 = getRndPoint(3);
	Polygon poly3 = getRndPolygon(3, 1);
	
	Polygon poly4 = poly3 + p4; // Add polygon and point to get polygon.
	std::cout << "Add polygon and point. Get a polygon.\n";
	std::cout << poly3 << " + " << p4 << " = " << poly4 << "\n\n";

	Polygon poly5 = getRndPolygon(2, 1);
	Line l4 = getRndLine(2);

	Polygon poly6 = l4 + poly5; // Add line and polygon to get polygon.
	std::cout << "Add line and polygon. Get a polygon.\n";
	std::cout << l4 << " + " << poly5 << " = " << poly6 << "\n\n";

	Polygon poly7 = getRndPolygon(2, 1);
	Polygon poly8 = getRndPolygon(2, 1);
	Polygon poly9 = poly7 + poly8; // Add two polygons to get a polygon.
	std::cout << "Add two polygons. Get a polygon.\n";
	std::cout << poly7 << " + " << poly8 << " = " << poly9 << "\n\n";
}

// Function to test if writing and reading points, lines and polygons to files works as intended.
void TestFileWritingAndReading()
{
	//Vectors filled randomly first.
	std::vector<Point> points_before;
	std::vector<Line> lines_before;
	std::vector<Polygon> polygons_before;

	//Vectors that will be read in from files.
	std::vector<Point> points_after;
	std::vector<Line> lines_after;
	std::vector<Polygon> polygons_after;

	std::ofstream ofs("Objects.txt", std::ios::trunc); // Open filestream. Truncate fail.

	for (unsigned int i = 0; i < 1000; i++) // Make a 1000 points, lines or polygons.
	{
		unsigned int rnd = rand() % 3; //Randomly choose point, line or polygon.
		unsigned int axis = (rand() % 2) + 2; //Randomly choose axis. Will choose 2 or 3.

		// Randomly write points, lines and polygons to file.
		if (rnd == 0) // Do point.
		{
			points_before.push_back(getRndPoint(axis));
			ofs << points_before[points_before.size() - 1];
		}
		else if (rnd == 1) //Do line. 
		{
			lines_before.push_back(getRndLine(axis));
			ofs << lines_before[lines_before.size() - 1];
		}
		else if (rnd == 2) // Do polygon.
		{
			polygons_before.push_back(getRndPolygon(axis));
			ofs << polygons_before[polygons_before.size() - 1];
		}
	}
	ofs.close(); //Close filestream.

	// Read from file back to points, lines and polygons.
	std::ifstream ifs("Objects.txt");

	while (!ifs.eof()) // Read to end of file.
	{
		//Each >> operator should check if the incoming type is the right type. 
		Point point; //Make a default point.
		ifs >> point; //Try to put next element in stream into point. If it is a line or polygon, nothing should happen here.

		Line line;
		ifs >> line;

		Polygon polygon(2); //Polygon needs a nr of axis as constructor argument. This should be overwritten, if the polygon in the file is a 3D point.
		ifs >> polygon;

		//Only push_back the element that is set.
		if (!point.unset())
			points_after.push_back(point);
		if (!line.unset())
			lines_after.push_back(line);
		if (polygon.size() > 0)
			polygons_after.push_back(polygon);
	}
	ifs.close(); //Close filestream.

	//Compare the vectors before with the vectors after. If they are all equal, the test was successful.

	//Points comparison.
	if (points_after == points_before)
		std::cout << "Points: Success.\n";
	else
		std::cout << "Points: Failure.\n";

	//Lines comparison.
	if (lines_after == lines_before)
		std::cout << "Lines: Success.\n";
	else
		std::cout << "Lines: Failure.\n";

	//Points comparison.
	if (polygons_after == polygons_before)
		std::cout << "Polygon: Success.\n";
	else
		std::cout << "Polygon: Failure.\n";

}

int main()
{
	srand(time(NULL)); //rand() used for some of the function. Set seed here.

	//TestPointAxisRestraint();
	//TestSimplePolygonFunctionality();
	//TestPolygonRemoveRedundantPointFunctionality();
	//TestAxisMismatchException();
	TestOperatorOverloads();
	//TestFileWritingAndReading();

	system("pause");
	return 0;
}