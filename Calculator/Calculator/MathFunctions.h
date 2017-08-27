#pragma once

class MathFunctions
{
private:
	double(*mathFunc)(double);
public:
	MathFunctions();
	MathFunctions(double(*start_mathFunc)(double));
	void set(double(*start_mathFunc)(double));
	double doOperation(double);
};