#include <sstream>
#include <iostream>
#include <string>
#include <vector>
//#include <math.h>
#include "BasicMathFuncs.h"

namespace MyConsts
{
	const int paranthesis_start = -1;
	const int parantesis_end = -2;

	const int number_of_consts = 2;
}

class Operators
{
	int key;
	int priority;
	int exp_fix;

	double(*mathFunc) (double, double);

public:
	Operators()
	{
		key = priority = exp_fix = 0;
		mathFunc = NULL;
	}
	Operators(int start_key, int start_priority, double(*startMathFunc)(double, double), int start_exp_fix = 0)
	{
		key = start_key;
		priority = start_priority;
		exp_fix = start_exp_fix;

		mathFunc = startMathFunc;
	}
	int getKey()
	{
		return key;
	}
	int getPriority()
	{
		return priority;
	}
	int getNextPriority()
	{
		return priority + exp_fix;
	}
	double doOperation(double d1, double d2)
	{
		return mathFunc(d1, d2);
	}
	std::string getString()
	{
		std::stringstream ss;
		ss << key << "   " << priority << "   " << exp_fix;
		return ss.str();
	}
};

void clearInput(std::istringstream &is)
{
	is.clear();
	is.ignore(INT_MAX, '\n');
}

double runCalc(int start_priority, std::vector<int> &iInputString, std::vector<double> &dNumber, std::vector<Operators> &operators, int &index, bool start_params_set = false,
	double start_value = 0, Operators start_operator = Operators())
{
	//std::cout << "Start of Func\n";
	double ans = 0;
	while (index < iInputString.size())
	{
		//std::cout << "Start of while\n";
		if (iInputString[index] == MyConsts::paranthesis_start)
		{
			//std::cout << "If 1\n";
			ans = runCalc(-1, iInputString, dNumber, operators, ++index);
			std::cout << "( : " << ans << '\n';
		}
		else if (iInputString[index] == MyConsts::parantesis_end)
		{
			//std::cout << "If 2\n";
			//if (index + 1 != iInputString.size())
			//{
			//	index++;
			//}
			index++;
			std::cout << ") : " << ans << '\n';
			return ans;
		}
		else if (iInputString[index] >= 0) //Is a number.
		{
			//std::cout << "If 3\n";
			ans = dNumber[iInputString[index]];
			index++;
		}
		else if (iInputString[index] <= operators[0].getKey() && iInputString[index] >= operators[operators.size() - 1].getKey()) //Is an operator.
		{
			//std::cout << "If 4	" << -(iInputString[index] + 1 + MyConsts::number_of_consts) << "\n";
			Operators op = operators[-(iInputString[index] + 1 + MyConsts::number_of_consts)];
			if (op.getNextPriority() >= start_priority)
			{
				//std::cout << "If 41\n";
				std::cout << "Mellom (f�r): " << ans << '\n';
				ans = op.doOperation(ans, runCalc(op.getPriority(), iInputString, dNumber, operators, ++index));
				std::cout << "Mellom (etter): " << ans << '\n';
			}
			else
			{
				//std::cout << "If 41\n";
				return ans;
			}
		}
	}
	return ans;
}

double runCalc2(int start_priority, std::vector<int> &iInputString, std::vector<double> &dNumber, std::vector<Operators> &operators, int &index, bool start_params_set = false,
	double start_value = 0, Operators start_operator = Operators())
{
	std::cout << "VERY START" << '\n';
	int priority = 2;
	double ans = start_value;
	Operators op = start_operator;
	if (!start_params_set)
	{
		if (iInputString[index] == MyConsts::paranthesis_start)
		{
			ans = runCalc(-1, iInputString, dNumber, operators, ++index);
			//ans = ans!;
		}
		//else if (iInputString[index] == isMathFunction)
		//{
		//	ans = runCalc(??)
		//}
		else if (iInputString[index] == MyConsts::parantesis_end)
		{
			return ans;
		}
		else if (iInputString[index] >= 0) //Is a number
		{
			ans = dNumber[iInputString[index]];
			//ans = ans!;
		}
		index++;
		if (iInputString[index] == MyConsts::parantesis_end)
		{
			return ans;
		}
		op = operators[-(iInputString[index] + 1 + MyConsts::number_of_consts)];
		index++;
		std::cout << "END OF START" << '\n';
	}
	double nr;
	while ((index + 1 <= iInputString.size() - 1 && iInputString[index] != MyConsts::parantesis_end) && op.getPriority() > start_priority) {
		std::cout << "START OF WHILE" << '\n';
		if (iInputString[index] == MyConsts::paranthesis_start)
		{
			nr = runCalc(-1, iInputString, dNumber, operators, index);
			//nr = nr!;
			ans = op.doOperation(ans, nr);
		}
		//else if (iInputString[index] == aMathFunc)
		//{
		//	//
		//}
		else if (iInputString[index] == MyConsts::parantesis_end)
		{
			return ans;
		}
		else if (iInputString[index] >= 0) //Is a number.
		{
			nr = dNumber[iInputString[index]];
			//nr = nr!;
			if (index + 1 <= iInputString.size() - 1 && iInputString[index+1] != MyConsts::parantesis_end &&
				operators[-(iInputString[index + 1] + 1 + MyConsts::number_of_consts)].getNextPriority() > op.getPriority())
			{
				Operators nextOp = operators[-(iInputString[index + 1] + 1 + MyConsts::number_of_consts)];
				index += 2;
				nr = runCalc(priority, iInputString, dNumber, operators, index, true, nr, nextOp);
			}
			
			ans = op.doOperation(ans, nr);
		}
		index++;
		if (index + 1 <= iInputString.size() - 1 && iInputString[index + 1] != MyConsts::parantesis_end)
		{
			op = operators[-(iInputString[index] + 1 + MyConsts::number_of_consts)];
		}
		std::cout << "END OF WHILE" << '\n';
	}
	return ans;
}

void test1()
{
	std::string sa[] = { "14","+","2","*","33" };
	std::string s1 = "14+2*33";
	std::string s2 = "(add(14,mul(2,33)))";

	std::string si = "(20.3+4.6*-16.32)";

	double d[] = { 20.3,4.6,-16.32 };
	int i[] = { -10,0,-1,1,-3,2,-11 };
}

void insertMissingAddOperators(std::vector<int> &iInputString)
{
	for (int i = 0; i < iInputString.size() - 1; i++)
	{
		if (iInputString[i] >= 0 && iInputString[i+1] >= 0)
		{
			iInputString.insert(iInputString.begin() + i++ + 1, -3);
		}
	}
}

void checkForLegalSymbol(std::istringstream &is, std::vector<int> &iInputString)
{
	is.clear();
	std::string legalChars = "()+-*/";
	char c;
	is >> c;
	for (int i = 0; i < legalChars.length(); i++)
	{
		if (c == legalChars[i])
		{
			iInputString.push_back(-(i+1));
			return;
		}
	}
	std::cout << "FAIL!!!\n";
	clearInput(is);
}

void runTest2(std::string &sInputString)
{
	int key = -1 - MyConsts::number_of_consts;
	std::vector<Operators> operators;
	operators.push_back(Operators(key--, 0, add));
	operators.push_back(Operators(key--, 0, sub));
	operators.push_back(Operators(key--, 1, mul));
	operators.push_back(Operators(key--, 1, div));
	operators.push_back(Operators(key--, 1, mod));
	operators.push_back(Operators(key--, 2, pow, 1));

	std::vector<int> iInputString;
	std::vector<double> dNumbers;
	sInputString = "(" + sInputString + ")";
	std::istringstream is(sInputString);
	double d1;
	while (is.rdbuf()->in_avail() > 0)
	{
		is >> d1;
		if (is.fail())
		{
			checkForLegalSymbol(is, iInputString);
		}
		else
		{
			dNumbers.push_back(d1);
			iInputString.push_back(dNumbers.size() - 1);
		}
	}
	insertMissingAddOperators(iInputString);
	int index = 1;
	double answer = runCalc(-1, iInputString, dNumbers, operators, index);
	//std::cout << "[\t";
	//for (int i = 0; i < iInputString.size(); i++)
	//{
	//	std::cout << iInputString[i] << '\t';
	//}
	//std::cout << "]\n";
	std::cout << answer << '\n';
}

void test2()
{
	std::string sInputString;
	std::getline(std::cin, sInputString);
	while (sInputString.length() > 0)
	{
		runTest2(sInputString);
		std::getline(std::cin, sInputString);
	}
}

class C1
{
	int key;
	int priority;
	int exp_fix;

	double(*mathFunc) (double, double);

public:
	C1(int start_key, int start_priority, double(*startMathFunc)(double, double), int start_exp_fix=0)
	{
		key = start_key;
		priority = start_priority;
		exp_fix = start_exp_fix;
		
		mathFunc = startMathFunc;
	}
	int getKey()
	{
		return key;
	}
	int getPriority()
	{
		return priority;
	}
	int getNextPriority()
	{
		return priority + exp_fix;
	}
	double doOperation(double d1, double d2)
	{
		return mathFunc(d1, d2);
	}
	std::string getString()
	{
		std::stringstream ss;
		ss << key << "   " << priority << "   " << exp_fix;
		return ss.str();
	}
};

double sin12(double d1)
{
	return sin(d1);
}
double cos12(double d1)
{
	return tan(d1);
}

double funcfunc(double (*aFunc)(double), double d1)
{
	return aFunc(d1);
}

void test3()
{
	std::vector<C1> mathVector;
	mathVector.push_back(C1(-1, 0, add));
	mathVector.push_back(C1(-2, 0, sub));
	mathVector.push_back(C1(-3, 1, mul));
	mathVector.push_back(C1(-4, 1, div, -1));
	mathVector.push_back(C1(-5, 1, mod, -1));
	mathVector.push_back(C1(-6, 2, pow));

	for (int i = 0; i < mathVector.size(); i++)
	{
		std::cout << mathVector[i].getString() << "   " << mathVector[i].doOperation(5,3) << '\n';
	}
	//std::cout << funcfunc(abs, -13) << '\n';
	//C1 c1(-1, 0, add);
	//C1 c2(-3, 1, mul);
	//C1 c3(-6, 2, pow, 1);
	//std::cout << c1.getString() << "   " << c1.doOperation(3,3) << '\n';
	//std::cout << c2.getString() << "   " << c2.doOperation(3,3) << '\n';
	//std::cout << c3.getString() << "   " << c3.doOperation(3,3) << '\n';
}

int main()
{
	//unsigned int y = 1024;
	//int bits = 0;
	//while (y != 0)
	//{
	//	y >>= 1;
	//	bits++;
	//}
	//
	//int x = -4;
	//
	//y >>= 6;
	//std::cout << bits << '\n';
	test2();
	//test3();

	system("PAUSE");
	return 0;
}