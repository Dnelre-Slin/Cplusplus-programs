#include "MathFunctions.h"

/*Class that makes functions easier to handle in runCalc. Similar to Operator.cpp for operators.*/
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
	mathFunc = start_mathFunc; //Pointer to this particular math function. This can be functions like tan, sin, acos and ln.
}
double MathFunctions::doOperation(double d)
{
	return mathFunc(d); //Do math function operation.
}