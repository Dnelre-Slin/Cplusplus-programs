#include <sstream>
#include <iostream>
#include <string>
#include <vector>
//#include <math.h>
#include "BasicMathFuncs.h"

enum MyConsts
{
	paranthesis_start	= -1,
	parantesis_end		= -2,

	number_of_consts	=  2,

	first_operator		= -3,
	plus				= -3,
	minus				= -4,
	multiply			= -5,
	divide				= -6,
	modulo				= -7,
	exponantial			= -8,
	last_operator		= -8
};

class Operators
{
	int key;
	int priority;
	int exp_fix;

	double(*mathFunc) (double, double);

public:
	Operators(int start_key, int start_priority, double(*startMathFunc)(double, double), int start_exp_fix = 0)
	{
		key      = start_key;
		priority = start_priority;
		exp_fix  = start_exp_fix;

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

double runCalc(int start_priority, std::vector<int> &iInputString, std::vector<double> &dNumber, std::vector<Operators> &operators, int &index)
{
	double ans = 0;
	while (index < iInputString.size())
	{
		//std::cout << iInputString[index] << "     Heng deg!!\n";
		if (iInputString[index] == MyConsts::paranthesis_start)
		{
			ans = runCalc(-1, iInputString, dNumber, operators, ++index);
			index++;
		}
		else if (iInputString[index] == MyConsts::parantesis_end)
		{
			return ans;
		}
		else if (iInputString[index] >= 0) //Is a number.
		{
			ans = dNumber[iInputString[index]];
			index++;
		}
		else if (iInputString[index] <= operators[0].getKey() && iInputString[index] >= operators[operators.size() - 1].getKey()) //Is an operator.
		{
			Operators op = operators[-(iInputString[index] + 1 + MyConsts::number_of_consts)];
			if (op.getNextPriority() > start_priority)
			{
				ans = op.doOperation(ans, runCalc(op.getPriority(), iInputString, dNumber, operators, ++index));
			}
			else
			{
				return ans;
			}
		}
		else
		{
			std::cout << "MATH ERROR!!!!!\n";
		}
	}
	return ans;
}

/*
double runCalc3(int start_priority, std::vector<int> &iInputString, std::vector<double> &dNumber, std::vector<Operators> &operators, int &index, bool start_params_set = false,
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
			std::cout << "( : " << ans << " is lost!!\n";
			ans = runCalc(-1, iInputString, dNumber, operators, ++index);
			index++;
			std::cout << "( : " << ans << '\n';
		}
		else if (iInputString[index] == MyConsts::parantesis_end)
		{
			//std::cout << "If 2\n";
			//if (index + 1 != iInputString.size())
			//{
			//	index++;
			//}
			//index++;
			std::cout << ") : " << ans << '\n';
			return ans;
		}
		else if (iInputString[index] >= 0) //Is a number.
		{
			//std::cout << "If 3\n";
			std::cout << "(Is nr): " << ans << " is lost!!\n";
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
				std::cout << "Mellom (før): " << ans << '\n';
				ans = op.doOperation(ans, runCalc(op.getPriority(), iInputString, dNumber, operators, ++index));
				std::cout << "Mellom (etter): " << ans << '\n';
			}
			else
			{
				//std::cout << "If 41\n";
				std::cout << "(Operator return): " << ans << '\n';
				return ans;
			}
		}
	}
	return ans;
}

double runCalc2(int start_priority, std::vector<int> &iInputString, std::vector<double> &dNumber, std::vector<Operators> &operators, int &index)
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
				nr = runCalc2(priority, iInputString, dNumber, operators, index, true, nr, nextOp);
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
*/

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
	std::string legalChars = "()+-*/%^";
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

int getKeyOfOperator(char c, std::string &legalOperator)
{
	for (int i = 0; i < legalOperator.length(); i++)
	{
		if (c == legalOperator[i])
		{
			return -(i + 1 + MyConsts::number_of_consts);
		}
	}
	return 0; // If c is not a legal operator.
}

//Checks if a key is an operator in MyConsts.
bool isOperator(int key)
{
	if (key <= MyConsts::first_operator && key >= MyConsts::last_operator)
	{
		return true;
	}
	return false;
}


//  Gets all consecutive + and -, that are not considered operators, but signs, and reduces it to nothing, if sign is positive, or a "-1*" sentence in iInput if negative.
bool isSign(std::istringstream &istream, std::vector<int> &iInput, std::vector<double> &dNumbers)
{
	char c = istream.peek();
	if (c == '+' || c == '-')
	{
		bool is_positive = true;
		while (c == '+' || c == '-') {
			if (c == '-') {
				is_positive = !is_positive; //Swap between positive and negative, everytime minus sign shows up
			}
			istream >> c;
			c = istream.peek();
		}
		if (!is_positive)
		{
			dNumbers.push_back(-1); //Insert negative one, to make the following statement or number negative.
			iInput.push_back(dNumbers.size() - 1);
			iInput.push_back(MyConsts::multiply); 
		}
		return true;
	}
	return false;
}

bool isNumber(std::istringstream &istream, std::vector<int> &iInput, std::vector<double> &dNumbers)
{
	if (iInput.back() == MyConsts::parantesis_end) //Auto-places '*', if number comes right behind ')'.
	{ //(Should also consider factorial and variables here.)
		iInput.push_back(MyConsts::multiply);
	}
	double d;
	istream >> d;
	if (istream.fail()) //Not a number.
	{
		istream.clear(); //Clear failbit.
		return false;
	}
	dNumbers.push_back(d); //Puts number in double vector.
	iInput.push_back(dNumbers.size() - 1); //And index to that number in int vector.
	return true;
}

bool handleInputString(std::istringstream &istream, std::vector<int> &iInput, std::vector<double> &dNumbers, std::string &legalOperator)
{
	char c;
	int op_key = 0;
	iInput.push_back(-1); //Auto-place first start parantesis.
	while (istream.rdbuf()->in_avail() > 0)
	{
		c = istream.peek();
		if (c == '(')
		{
			if (iInput.back() >= 0 || iInput.back() == MyConsts::parantesis_end) // Is a number or an end parantesis. (Factorial should also be here).
			{
				iInput.push_back(MyConsts::multiply);
			}
			iInput.push_back(MyConsts::paranthesis_start);
			istream >> c;
		}
		else if (c == ')' && ((iInput.back() >= 0) || iInput.back() == MyConsts::parantesis_end)) //Last element is a number. (Factorial should also be here).
		{
			iInput.push_back(MyConsts::parantesis_end);
			istream >> c;
		}
		//else if (c == '!') //If c is factorial symbol.
		//{
		//	//
		//}
		else if (isOperator(op_key = getKeyOfOperator(c, legalOperator)) && isOperator(iInput.back()))
		//else if (((op_key = getKeyOfOperator(c, legalOperator)) <= -3) && (!((iInput.back() <= -3 && iInput.back() >= -8) || (iInput.back() == -1)))) // If is operator and back is not operator or (.
		{// If c is an operator and back() is not an operator and not a '('. (Functions should also be here).
			iInput.push_back(op_key);
			istream >> c;
		}
		else if (isSign(istream, iInput, dNumbers) /* || isLetter() */ || isNumber(istream, iInput, dNumbers))
		{
			//No need for body. Everything handled in isSign, isLetter and isNumber functions.
		}
		else // If it makes it this far, there must be a syntax error, since all possible legal options should be covered in the if's.
		{
			return false; //Syntax error.
		}
	}
	iInput.push_back(MyConsts::parantesis_end); //Auto-place last end parantesis.
	return true; //No syntax errors. Math string parsed successfully.
}

void runTest2(std::string &iString)
{
	std::string legalOperators = "+-*/%^";
	int key = -1 - MyConsts::number_of_consts;
	std::vector<Operators> operators;
	operators.push_back(Operators(key--, 0, add));
	operators.push_back(Operators(key--, 0, sub));
	operators.push_back(Operators(key--, 1, mul));
	operators.push_back(Operators(key--, 1, div));
	operators.push_back(Operators(key--, 1, mod));
	operators.push_back(Operators(key--, 2, pow, 1));

	std::istringstream istream(iString);
	std::vector<int> iInput;
	std::vector<double> dNumbers;
	//sInputString = "(" + sInputString + ")";
	//std::istringstream istream(sInputString);
	//double d1;
	//while (is.rdbuf()->in_avail() > 0)
	//{
	//	is >> d1;
	//	if (is.fail())
	//	{
	//		checkForLegalSymbol(is, iInputString);
	//	}
	//	else
	//	{
	//		dNumbers.push_back(d1);
	//		iInputString.push_back(dNumbers.size() - 1);
	//	}
	//}
	//insertMissingAddOperators(iInputString);
	if (handleInputString(istream, iInput, dNumbers, legalOperators))
	{
		for (int i = 0; i < iInput.size(); i++) 
		{
			//std::cout << iInput[i] << '\n';
			if (iInput[i] >= 0)
			{
				std::cout << dNumbers[iInput[i]];
			}
			else
			{
				std::cout << legalOperators[-(iInput[i]) - 1];
			}
		}
		std::cout << " = ";
		int index = 1;
		double answer = runCalc(-1, iInput, dNumbers, operators, index);
		//std::cout << "[\t";
		//for (int i = 0; i < iInputString.size(); i++)
		//{
		//	std::cout << iInputString[i] << '\t';
		//}
		//std::cout << "]\n";
		std::cout << answer << '\n';
	}
	else
	{
		std::cout << "Syntax error.\n";
	}
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