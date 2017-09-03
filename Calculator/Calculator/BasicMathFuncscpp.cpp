#include <stdexcept>
#include "BasicMathFuncs.h"
namespace MyMath
{

	double MyMath::add(double d1, double d2)
	{
		return d1 + d2;
	}
	double MyMath::sub(double d1, double d2)
	{
		return d1 - d2;
	}
	double MyMath::mul(double d1, double d2)
	{
		return d1 * d2;
	}
	double MyMath::div(double d1, double d2)
	{
		if (d2 == 0)
		{
			throw std::runtime_error("Math Error. (Divide by zero exception)");
		}
		return d1 / d2;
	}
	double MyMath::mod(double d1, double d2)
	{
		if (d2 == 0)
		{
			throw std::runtime_error("Math Error. (Modulo by zero exception)");
		}
		return int(d1) % int(d2);
	}
	double MyMath::root(double root_nr, double d1)
	{
		return pow(d1, (1 / root_nr));
	}
	double MyMath::doFactorial(double i1, double stop_nr)
	{
		if (i1 == stop_nr)
		{
			return 1;
		}
		return i1 * doFactorial(i1 - 1, stop_nr);
	}
	void MyMath::factorialExceptionChecks(double d1, double d2, std::string type)
	{
		if (d1 < 0 || d2 < 0)
		{
			throw std::runtime_error("Math Error. (" + type + " of negative number exception)");
		}
		if (type != "Factorial" && d2 > d1)
		{
			throw std::runtime_error("Math Error. (" + type + ": r greater than n exception)");
		}
		long long i1 = d1;
		long long i2 = d2;
		if (i1 != d1 || i2 != d2)
		{
			throw std::runtime_error("Math Error. (" + type + " of non-integer exception)");
		}
	}
	double MyMath::factorial(double d1)
	{
		factorialExceptionChecks(d1, 0, "Factorial");
		return doFactorial(d1, 0);
	}
	double MyMath::nPr(double d1, double d2)
	{
		factorialExceptionChecks(d1, d2, "nPr");
		return doFactorial(d1, (d1 - d2));
	}
	double MyMath::nCr(double d1, double d2)
	{
		factorialExceptionChecks(d1, d2, "nCr");
		if (d2 > (d1 - d2))
		{
			return doFactorial(d1, d2) / doFactorial((d1 - d2), 0);
		}
		return doFactorial(d1, (d1 - d2)) / doFactorial(d2, 0);
	}
	double MyMath::logBase(double base, double d1)
	{
		return (log10(d1) / log10(base));
	}
};
