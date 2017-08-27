#include "MathFunctions.h"

MathFunctions::MathFunctions()
{
	mathFunc = nullptr;
}
MathFunctions::MathFunctions(double(*start_mathFunc)(double))
{
	set(start_mathFunc);
}
void MathFunctions::set(double(*start_mathFunc)(double))
{
	mathFunc = start_mathFunc;
}
double MathFunctions::doOperation(double d)
{
	return mathFunc(d);
}