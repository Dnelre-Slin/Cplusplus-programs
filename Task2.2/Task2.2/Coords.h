#pragma once

struct Coord2D
{
	int x, y;
	Coord2D() {};
	Coord2D(int _x, int _y) : 
		x(_x), 
		y(_y) {}
};

struct Coord3D
{
	int x, y, z;
	Coord3D() {};
	Coord3D(int _x, int _y, int _z) :
		x(_x),
		y(_y),
		z(_z) {}
};