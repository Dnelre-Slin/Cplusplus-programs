#pragma once

struct Coords
{
	std::string test() const { return "Abstract"; }
	static const int i = 0;
};

struct Coords2D : public Coords
{
	static const int i = 1;

	int x, y;
	Coords2D(int _x = 0, int _y = 0) : x(_x), y(_y){}
	std::string test() const { return "2D"; }
};

struct Coords3D : public Coords
{
	static const int i = 2;

	int x, y, z;
	Coords3D(int _x = 0, int _y = 0, int _z = 0) : x(_x), y(_y), z(_z){}
	std::string test() const { return "3D"; }
};