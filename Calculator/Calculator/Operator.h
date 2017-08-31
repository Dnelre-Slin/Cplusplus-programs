#pragma once

class Operators
{
private:
	int priority;
	int pow_fix;

	double(*mathFunc) (double, double);

public:
	Operators();
	Operators(int start_priority, double(*startMathFunc)(double, double), int start_pow_fix = 0);
	void set(int start_priority, double(*startMathFunc)(double, double), int start_pow_fix = 0);
	int getPriority();
	int getNextPriority();
	double doOperation(double d1, double d2);
};