#pragma once
#include <string>

namespace MyMath
{
	double add(double d1, double d2);
	double sub(double d1, double d2);
	double mul(double d1, double d2);
	double div(double d1, double d2);
	double mod(double d1, double d2);
	double root(double d1, double d2);
	long long doFactorial(double i1, double stop_nr);
	void factorialExceptionChecks(double d1, double d2, std::string type);
	double factorial(double d1);
	double nPr(double d1, double d2);
	double nCr(double d1, double d2);
	double logBase(double d1, double d2);
};
