#include "Operator.h"

Operators::Operators()
{
	priority = 0;
	pow_fix = 0;

	mathFunc = nullptr;
}
Operators::Operators(int start_priority, double(*startMathFunc)(double, double), int start_pow_fix)
{
	set(start_priority, startMathFunc, start_pow_fix);
}
void Operators::set(int start_priority, double(*startMathFunc)(double, double), int start_pow_fix)
{
	priority = start_priority;
	pow_fix = start_pow_fix;

	mathFunc = startMathFunc;
}
int Operators::getPriority()
{
	return priority;
}
int Operators::getNextPriority()
{
	return priority + pow_fix;
}
double Operators::doOperation(double d1, double d2)
{
	return mathFunc(d1, d2);
}