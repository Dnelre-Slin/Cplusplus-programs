#pragma once

class Operators
{
	int key;
	int priority;
	int exp_fix;

	double(*mathFunc) (double, double);

public:
	Operators();
	Operators(int start_key, int start_priority, double(*startMathFunc)(double, double), int start_exp_fix = 0);
	void set(int start_key, int start_priority, double(*startMathFunc)(double, double), int start_exp_fix = 0);
	int getKey();
	int getPriority();
	int getNextPriority();
	double doOperation(double d1, double d2);
};