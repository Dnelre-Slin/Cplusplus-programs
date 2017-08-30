#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <unordered_map>
//#include <math.h>
//#include <cmath>
#include "BasicMathFuncs.h"
#include "Operators.h"

//enum MyConsts
//{
//	paranthesis_start	= -1,
//	parantesis_end		= -2,
//
//	number_of_consts	=  2,
//
//	first_operator		= -3,
//	plus				= -3,
//	minus				= -4,
//	multiply			= -5,
//	divide				= -6,
//	modulo				= -7,
//	exponantial			= -8,
//	last_operator		= -8
//};

//class Operators
//{
//	int key;
//	int priority;
//	int exp_fix;
//
//	double(*mathFunc) (double, double);
//
//public:
//	Operators(int start_key, int start_priority, double(*startMathFunc)(double, double), int start_exp_fix = 0)
//	{
//		key      = start_key;
//		priority = start_priority;
//		exp_fix  = start_exp_fix;
//
//		mathFunc = startMathFunc;
//	}
//	int getKey()
//	{
//		return key;
//	}
//	int getPriority()
//	{
//		return priority;
//	}
//	int getNextPriority()
//	{
//		return priority + exp_fix;
//	}
//	double doOperation(double d1, double d2)
//	{
//		return mathFunc(d1, d2);
//	}
//};

class Calculator
{
	// Some constants used to make code look more readable.
	int const_count = 0;

	// Plain constants
	const int c_paranthesis_start		= --const_count;
	const int c_paranthesis_end			= --const_count;
	const int c_factorial				= --const_count;
	
	const int c_number_of_plain_const	=  -const_count;

	// Operator constants
	const int c_plus					= --const_count;
	const int c_first_operator			=   const_count;
	const int c_minus					= --const_count;
	const int c_multiply				= --const_count;
	const int c_divide					= --const_count;
	const int c_modulo					= --const_count;
	const int c_exponential				= --const_count;
	const int c_last_operator			=   const_count;

	const int c_number_of_operators		= -const_count-c_number_of_operators;
	
	// End of constant declarations. (Variable const_count, should not be used beyond this point.)

	std::vector<int>		iInput;    //Holds mathematical sentence to be processed by runCalc method. All symbols will have negative values, and numbers will be positive.
	std::vector<double>		dNumbers;  //Holds the actual numbers. iInput only holds index of the numbers in dNumbers. So numbers can be negative, but it's index will always be positive.
	std::vector<Operators>	operators; //Holds all the operators to be used. Can run mathematical function directly from operator objects.

	std::string legalOperators;

	double runCalc(int start_priority, int &index)
	{
		double ans = 0;
		while (index < iInput.size())
		{
			if (iInput[index] == c_paranthesis_start)
			{
				ans = runCalc(-1, ++index);
				index++;
			}
			else if (iInput[index] == c_paranthesis_end)
			{
				return ans;
			}
			else if (iInput[index] == c_factorial)
			{
				ans = factorial(ans);
				index++;
			}
			else if (iInput[index] >= 0) //Is a number.
			{
				ans = dNumbers[iInput[index]];
				index++;
			}
			else if (iInput[index] <= operators[0].getKey() && iInput[index] >= operators[operators.size() - 1].getKey()) //Is an operator.
			{
				Operators op = operators[-(iInput[index] + 1 + c_number_of_plain_const)];
				if (op.getNextPriority() > start_priority)
				{
					ans = op.doOperation(ans, runCalc(op.getPriority(), ++index));
				}
				else
				{
					return ans;
				}
			}
			else
			{
				std::cout << "Should never happend!!!!!\n";
			}
		}
		return ans;
	}

	int getKeyOfOperator(char c)
	{
		for (int i = 0; i < legalOperators.length(); i++)
		{
			if (c == legalOperators[i])
			{
				return -(i + 1 + c_number_of_plain_const);
			}
		}
		return 0; // If c is not a legal operator.
	}

	//Checks if a key is an operator in MyConsts.
	bool isOperator(int key)
	{
		if (key <= c_first_operator && key >= c_last_operator)
		{
			return true;
		}
		return false;
	}

	//  Gets all consecutive + and -, that are not considered operators, but signs, and reduces it to nothing, if sign is positive, or a "-1*" sentence in iInput if negative.
	bool isSign(std::istringstream &istream)
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
				iInput.push_back(c_multiply);
			}
			return true;
		}
		return false;
	}

	bool isNumber(std::istringstream &istream)
	{
		if (iInput.back() == c_paranthesis_end || iInput.back() == c_factorial) //Auto-places '*', if number comes right behind end paranthesis or factorial.
		{ //(Should also consider factorial and variables here.)
			iInput.push_back(c_multiply);
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

	bool handleInputString(std::istringstream &istream)
	{
		char c;
		int op_key = 0;
		iInput.push_back(-1); //Auto-place first start parantesis.
		while (istream.rdbuf()->in_avail() > 0)
		{
			c = istream.peek();
			if (c == '(')
			{
				if (iInput.back() >= 0 || iInput.back() == c_factorial || iInput.back() == c_paranthesis_end) // Is a number, factorial or an end parantesis.
				{
					iInput.push_back(c_multiply);
				}
				iInput.push_back(c_paranthesis_start);
				istream >> c;
			}
			else if (c == ')' && ((iInput.back() >= 0) || iInput.back() == c_factorial || iInput.back() == c_paranthesis_end)) //Last element is a number, factorial or an end paranthesis.
			{
				iInput.push_back(c_paranthesis_end);
				istream >> c;
			}
			else if ((c == '!') && ((iInput.back() >= 0) || (iInput.back() == c_paranthesis_end))) //If c is '!' and last element is a number or an end parathesis.
			{
				iInput.push_back(c_factorial);
				istream >> c;
			}
			else if (isOperator(op_key = getKeyOfOperator(c)) && !isOperator(iInput.back()) && !(iInput.back() == c_paranthesis_start))
			{// If c is an operator and back() is not an operator and not a '('. (Functions should also be here).
				iInput.push_back(op_key);
				istream >> c;
			}
			else if (isSign(istream) /* || isLetter() */ || isNumber(istream))
			{
				//No need for body. Everything handled in isSign, isLetter and isNumber functions.
			}
			else // If it makes it this far, there must be a syntax error, since all possible legal options should be covered in the if's.
			{
				return false; //Syntax error.
			}
		}
		iInput.push_back(c_paranthesis_end); //Auto-place last end parantesis.
		return true; //No syntax errors. Math string parsed successfully.
	}

	void printInput()
	{
		for (int i = 0; i < iInput.size(); i++)
		{
			if (iInput[i] >= 0)
			{
				std::cout << dNumbers[iInput[i]];
			}
			else
			{
				if (iInput[i] == c_paranthesis_start)
				{
					std::cout << "(";
				}
				else if (iInput[i] == c_paranthesis_end)
				{
					std::cout << ")";
				}
				else if (iInput[i] == c_factorial)
				{
					std::cout << "!";
				}
				else
				{
					std::cout << legalOperators[-(iInput[i]) - 1 - c_number_of_plain_const];
				}
			}
		}
	}

	void calculatorLoop(std::string &sInputString)
	{
		std::istringstream istream(sInputString);
		if (handleInputString(istream))
		{
			printInput();
			int index = 1;
			try
			{
				double ans = runCalc(-1, index);
			std::cout << " = " << ans << '\n';
			}
			catch (std::runtime_error re)
			{
				std::cout << "Math Error. (" << re.what() << "(" << index << "))\n";
			}
		}
		else
		{
			std::cout << "Syntax Error.\n";
		}
	}

	void clearVectors()
	{
		iInput.clear();
		dNumbers.clear();
	}

public:
	Calculator()
	{
		legalOperators = "+-*/%^"; // <- Must be in the same order as the constants were declared.

		int key = -1 - c_number_of_plain_const;
		operators.push_back(Operators(key--, 0, add));
		operators.push_back(Operators(key--, 0, sub));
		operators.push_back(Operators(key--, 1, mul));
		operators.push_back(Operators(key--, 1, div));
		operators.push_back(Operators(key--, 1, mod));
		operators.push_back(Operators(key--, 2, pow, 1));

		startCalculator(); 
	}

	void startCalculator()
	{
		std::string sInputString;
		std::getline(std::cin, sInputString);
		while (sInputString.length() > 0) //Run till empty string is entered.
		{
			calculatorLoop(sInputString);
			clearVectors();
			std::getline(std::cin, sInputString);
		}
	}
};

//void clearInput(std::istringstream &is)
//{
//	is.clear();
//	is.ignore(INT_MAX, '\n');
//}

//double runCalc(int start_priority, std::vector<int> &iInputString, std::vector<double> &dNumber, std::vector<Operators> &operators, int &index)
//{
//	double ans = 0;
//	while (index < iInputString.size())
//	{
//		//std::cout << iInputString[index] << "     Heng deg!!\n";
//		if (iInputString[index] == MyConsts::paranthesis_start)
//		{
//			ans = runCalc(-1, iInputString, dNumber, operators, ++index);
//			index++;
//		}
//		else if (iInputString[index] == MyConsts::parantesis_end)
//		{
//			return ans;
//		}
//		else if (iInputString[index] >= 0) //Is a number.
//		{
//			ans = dNumber[iInputString[index]];
//			index++;
//		}
//		else if (iInputString[index] <= operators[0].getKey() && iInputString[index] >= operators[operators.size() - 1].getKey()) //Is an operator.
//		{
//			Operators op = operators[-(iInputString[index] + 1 + MyConsts::number_of_consts)];
//			if (op.getNextPriority() > start_priority)
//			{
//				ans = op.doOperation(ans, runCalc(op.getPriority(), iInputString, dNumber, operators, ++index));
//			}
//			else
//			{
//				return ans;
//			}
//		}
//		else
//		{
//			std::cout << "MATH ERROR!!!!!\n";
//		}
//	}
//	return ans;
//}

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
*/
//void checkForLegalSymbol(std::istringstream &is, std::vector<int> &iInputString)
//{
//	is.clear();
//	std::string legalChars = "()+-*/%^";
//	char c;
//	is >> c;
//	for (int i = 0; i < legalChars.length(); i++)
//	{
//		if (c == legalChars[i])
//		{
//			iInputString.push_back(-(i+1));
//			return;
//		}
//	}
//	std::cout << "FAIL!!!\n";
//	clearInput(is);
//}


//int getKeyOfOperator(char c, std::string &legalOperators)
//{
//	for (int i = 0; i < legalOperators.length(); i++)
//	{
//		if (c == legalOperators[i])
//		{
//			return -(i + 1 + MyConsts::number_of_consts);
//		}
//	}
//	return 0; // If c is not a legal operator.
//}
//
////Checks if a key is an operator in MyConsts.
//bool isOperator(int key)
//{
//	if (key <= MyConsts::first_operator && key >= MyConsts::last_operator)
//	{
//		return true;
//	}
//	return false;
//}
//
////  Gets all consecutive + and -, that are not considered operators, but signs, and reduces it to nothing, if sign is positive, or a "-1*" sentence in iInput if negative.
//bool isSign(std::istringstream &istream, std::vector<int> &iInput, std::vector<double> &dNumbers)
//{
//	char c = istream.peek();
//	if (c == '+' || c == '-')
//	{
//		bool is_positive = true;
//		while (c == '+' || c == '-') {
//			if (c == '-') {
//				is_positive = !is_positive; //Swap between positive and negative, everytime minus sign shows up
//			}
//			istream >> c;
//			c = istream.peek();
//		}
//		if (!is_positive)
//		{
//			dNumbers.push_back(-1); //Insert negative one, to make the following statement or number negative.
//			iInput.push_back(dNumbers.size() - 1);
//			iInput.push_back(MyConsts::multiply); 
//		}
//		return true;
//	}
//	return false;
//}
//
//bool isNumber(std::istringstream &istream, std::vector<int> &iInput, std::vector<double> &dNumbers)
//{
//	if (iInput.back() == MyConsts::parantesis_end) //Auto-places '*', if number comes right behind ')'.
//	{ //(Should also consider factorial and variables here.)
//		iInput.push_back(MyConsts::multiply);
//	}
//	double d;
//	istream >> d;
//	if (istream.fail()) //Not a number.
//	{
//		istream.clear(); //Clear failbit.
//		return false;
//	}
//	dNumbers.push_back(d); //Puts number in double vector.
//	iInput.push_back(dNumbers.size() - 1); //And index to that number in int vector.
//	return true;
//}
//
//bool handleInputString(std::istringstream &istream, std::vector<int> &iInput, std::vector<double> &dNumbers, std::string &legalOperators)
//{
//	char c;
//	int op_key = 0;
//	iInput.push_back(-1); //Auto-place first start parantesis.
//	while (istream.rdbuf()->in_avail() > 0)
//	{
//		c = istream.peek();
//		if (c == '(')
//		{
//			if (iInput.back() >= 0 || iInput.back() == MyConsts::parantesis_end) // Is a number or an end parantesis. (Factorial should also be here).
//			{
//				iInput.push_back(MyConsts::multiply);
//			}
//			iInput.push_back(MyConsts::paranthesis_start);
//			istream >> c;
//		}
//		else if (c == ')' && ((iInput.back() >= 0) || iInput.back() == MyConsts::parantesis_end)) //Last element is a number. (Factorial should also be here).
//		{
//			iInput.push_back(MyConsts::parantesis_end);
//			istream >> c;
//		}
//		//else if (c == '!') //If c is factorial symbol.
//		//{
//		//	//
//		//}
//		else if (isOperator(op_key = getKeyOfOperator(c, legalOperators)) && !isOperator(iInput.back()))
//		{// If c is an operator and back() is not an operator and not a '('. (Functions should also be here).
//			iInput.push_back(op_key);
//			istream >> c;
//		}
//		else if (isSign(istream, iInput, dNumbers) /* || isLetter() */ || isNumber(istream, iInput, dNumbers))
//		{
//			//No need for body. Everything handled in isSign, isLetter and isNumber functions.
//		}
//		else // If it makes it this far, there must be a syntax error, since all possible legal options should be covered in the if's.
//		{
//			return false; //Syntax error.
//		}
//	}
//	iInput.push_back(MyConsts::parantesis_end); //Auto-place last end parantesis.
//	return true; //No syntax errors. Math string parsed successfully.
//}
//
//void runTest2(std::string &iString)
//{
//	std::string legalOperators = "+-*/%^";
//	int key = -1 - MyConsts::number_of_consts;
//	std::vector<Operators> operators;
//	operators.push_back(Operators(key--, 0, add));
//	operators.push_back(Operators(key--, 0, sub));
//	operators.push_back(Operators(key--, 1, mul));
//	operators.push_back(Operators(key--, 1, div));
//	operators.push_back(Operators(key--, 1, mod));
//	operators.push_back(Operators(key--, 2, pow, 1));
//
//	std::istringstream istream(iString);
//	std::vector<int> iInput;
//	std::vector<double> dNumbers;
//	//sInputString = "(" + sInputString + ")";
//	//std::istringstream istream(sInputString);
//	//double d1;
//	//while (is.rdbuf()->in_avail() > 0)
//	//{
//	//	is >> d1;
//	//	if (is.fail())
//	//	{
//	//		checkForLegalSymbol(is, iInputString);
//	//	}
//	//	else
//	//	{
//	//		dNumbers.push_back(d1);
//	//		iInputString.push_back(dNumbers.size() - 1);
//	//	}
//	//}
//	//insertMissingAddOperators(iInputString);
//	if (handleInputString(istream, iInput, dNumbers, legalOperators))
//	{
//		for (int i = 0; i < iInput.size(); i++) 
//		{
//			//std::cout << iInput[i] << '\n';
//			if (iInput[i] >= 0)
//			{
//				std::cout << dNumbers[iInput[i]];
//			}
//			else
//			{
//				if (iInput[i] == MyConsts::paranthesis_start)
//				{
//					std::cout << "(";
//				}
//				else if (iInput[i] == MyConsts::parantesis_end)
//				{
//					std::cout << ")";
//				}
//				else
//				{
//					std::cout << legalOperators[-(iInput[i] + 1 + MyConsts::number_of_consts)];
//				}
//			}
//		}
//		std::cout << " = ";
//		int index = 1;
//		double answer = runCalc(-1, iInput, dNumbers, operators, index);
//		//std::cout << "[\t";
//		//for (int i = 0; i < iInputString.size(); i++)
//		//{
//		//	std::cout << iInputString[i] << '\t';
//		//}
//		//std::cout << "]\n";
//		std::cout << answer << '\n';
//	}
//	else
//	{
//		std::cout << "Syntax error.\n";
//	}
//}
//
//void test2()
//{
//	std::string sInputString;
//	std::getline(std::cin, sInputString);
//	while (sInputString.length() > 0)
//	{
//		runTest2(sInputString);
//		std::getline(std::cin, sInputString);
//	}
//}
/*
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
*/

int64_t longPow(int64_t i, int e)
{
	if (e == 0)
		return 1;
	return i * longPow(i, e - 1);
}

void commonFactors(int64_t &n1, int64_t &n2)
{
	int64_t low;
	if (n1 < n2)
	{
		if (!(n2 % n1))
		{
			n1 /= n1;
			n2 /= n1;
			return;
		}
		low = n1;
	}
	else
	{
		if (!(n1 % n2))
		{
			n1 /= n2;
			n2 /= n2;
			return;
		}
		low = n2;
	}
	/*int64_t low = (n1 < n2) ? n1 : n2;*/
	if (!(n1 % (low / 2) ||  n2 % (low / 2)))
	{
		n1 /= (low / 2);
		n2 /= (low / 2);
		return;
	}
	int64_t _n1 = n1, _n2 = n2;
	for (int64_t i = 3, j = low; i <= j; i += 2)
	{
		if (!(n1 % (low / i) || n2 % (low / i)))
		{
			n1 /= (low / i);
			n2 /= (low / i);
			return;
		}
		if (!(_n1 % (_n1 / i)))
		{
			_n1 /= (_n1 / i);
		}
		if (!(_n2 % (_n2 / i)))
		{
			_n2 /= (_n2 / i);
		}
	}
}

void findFactors(int64_t n)
{
	if (!(n % (n / 2)))
	{
		std::cout << "Factors of " << n << " are:   " << 2 << "  and   " << (n / 2) << '\n';
		return;
	}
	for (int64_t i = 3, j = sqrt(n); i <= j; i+=2)
	{
		if (!(n % (n / i)))
		{
			std::cout << "Factors of " << n <<" are:   " << i << "  and   " << (n / i) << '\n';
			return;
		}
	}
	std::cout << n << " is a prime number\n";
}
void findAllFactors(int64_t n)
{
	if (abs(sqrt(n)) >= 2)
	{
		if (!(n % (n / 2)))
		{
			std::cout << "   " << 2;
			findAllFactors(n / 2);
			return;
		}
		for (int64_t i = 3, j = sqrt(n); i <= j; i += 2)
		{
			if (!(n % (n / i)))
			{
				std::cout << "   " << i;
				findAllFactors(n / i);
				return;
			}
		}
	}
	std::cout << "   " << n << "\n";
}

void factorize(int64_t n1)
{
	int64_t n = n1;
	while (!(n % 2) && 2 <= sqrt(n1))
	{
		n /= 2;
		std::cout << 2 << "   ";
	}
	int64_t i = 3;
	while (i <= sqrt(n1))
	{
		if (!(n % i))
		{
			n /= i;
			std::cout << i << "   ";
		}
		else
		{
			i += 2;
		}
	}
	std::cout << n << "\n\n";
}

inline void swapNr(int64_t &n1, int64_t &n2)
{
	int h = n1;
	n1 = n2, n2 = h;
}

void smallestFraction(int64_t &n, int64_t &d)
{
	if (n % d == 0)
	{
		n /= d;
		d = 1;
		return;
	}
	int64_t x = n / d;
	n = n % d;
	smallestFraction(d, n);
	n = n + (x * d);
}

void shortenFraction(int64_t &n, int64_t &d)
{
	if (n == d)
	{
		n = 1;
		d = 1;
		return;
	}
	if (n > d)
	{
		if (!(n%d))
		{
			n /= d;
			d = 1;
			return;
		}
		int64_t x = n / d;
		n = n % d;
		smallestFraction(d, n);
		n = n + (x * d);
	}
	smallestFraction(d, n);
}

void test4()
{
	//int64_t i64 = INT64_MAX;
	//i64 = sqrtl(i64);
	//i64 = pow(i64, 2);
	//std::cout << i64 << "  " << sizeof(int64_t) <<  '\n';

	int64_t n1, n2;

	n1 = -4;
	n2 = 8;

	//n1 = -longPow(2, 60);
	//n2 = longPow(3, 35);

	//n1 = 12365474;
	//n1 = INT64_MAX - 543;

	std::cout << n1 << "  " << n2 << "\n\n";

	smallestFraction(n1, n2);

	//swapNr(n1, n2);

	//factorize(n1);

	//n1 = pow((int64_t)2,60);
	//n2 = pow((int64_t)3, 35);	
	//
	//std::cout << n1 << "  " << n2 << "\n\n";

	//findAllFactors(n1);
	//std::cout << std::endl;
	//findAllFactors(n2);
	//std::cout << "\n\n";

	//commonFactors(n1, n2);

	std::cout << n1 << "  " << n2 << "\n\n";

	//srand(time(NULL));

	//int64_t n = (int64_t)3000021389 * (int64_t)3000021389;

	//std::cout << n << '\n';

	//findFactors(n);

	//for (int i = 0; i < 100; i++)
	//{
	//	n = rand() + 3000000000;
	//	//std::cout << (n / 649913) << '\n';
	//	findFactors(n);
	//}
}

double bla(double d, double d2)
{
	return 2;
}

void test5()
{
	//std::hash_map<char, Operators> m;
	std::unordered_map<char, Operators> m;
	m['+'] = Operators(0,0,bla);
	//m['+'].set(0, 0, bla);
	//Operators op = Operators(0, 0, bla);
	//m.emplace('+',op);
	//m['b'] = Operators(0, 1, bla, 1);

	std::cout << m['+'].doOperation(1,1) << '\n';

	//std::cout << m['a'] << "  " << m['b'] << '\n';
}

void testCin()
{
	std::string s;
	std::cin >> s;
	std::cout << '\n' << s << '\n';
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
	//test2();
	//test3();

	//Calculator();

	//test4();

	//test5();

	testCin();

	system("PAUSE");
	return 0;
}