#pragma once

double add(double d1, double d2)
{
	return d1 + d2;
}
double sub(double d1, double d2)
{
	return d1 - d2;
}
double mul(double d1, double d2)
{
	return d1 * d2;
}
double div(double d1, double d2)
{
	if (d2 == 0)
	{
		throw std::runtime_error("Divide by zero exception");
	}
	return d1 / d2;
}
double mod(double d1, double d2)
{
	if (d2 == 0)
	{
		throw std::runtime_error("Modulo by zero exception");
	}
	return int(d1) % int(d2);
}
int doFactorial(int i1)
{
	if (i1 == 0 || i1 == 1)
	{
		return 1;
	}
	return i1 * doFactorial(i1 - 1);
}
double factorial(double d1)
{
	int i1 = d1;
	if (i1 != d1)
	{
		throw std::runtime_error("Factorial of non-integer exception");
	}
	return doFactorial(i1);
}
