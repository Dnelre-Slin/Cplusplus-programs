#include "Operator.h"

/*This class is used to make it easier to handle operators in runCalc method. Can store a math functions as a pointer, 
and easily call it with the doOperation method.*/
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
//Set the member variables.
void Operators::set(int start_priority, double(*startMathFunc)(double, double), int start_pow_fix)
{
	priority = start_priority; //The priority of this particular operator.
	pow_fix = start_pow_fix;   //Used to make sure the pow-operator is handled right to left.

	mathFunc = startMathFunc;  //Pointer to a math function. Most of them are in BasicMathFuncs.cpp
}
int Operators::getPriority()  //Get the priority of this operator. Used in runCalc.
{
	return priority;
}
int Operators::getNextPriority() //Same as above, but with added pow_fix. Pow_fix will be zero for every operator except pow.
{
	return priority + pow_fix; //Pow will return one higher on getNextPriority than on getPriority.
}
double Operators::doOperation(double d1, double d2)
{
	return mathFunc(d1, d2); //Do the math operation.
}