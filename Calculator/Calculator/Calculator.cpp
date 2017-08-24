#include <sstream>
#include <iostream>

#include "Calculator.h"
#include "BasicMathFuncs.h"

double Calculator::runCalc(int start_priority, int &index)
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
			ans = MyMath::factorial(ans);
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

int Calculator::getKeyOfOperator(char c)
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
bool Calculator::isOperator(int key)
{
	if (key <= c_first_operator && key >= c_last_operator)
	{
		return true;
	}
	return false;
}

//  Gets all consecutive + and -, that are not considered operators, but signs, and reduces it to nothing, if sign is positive, or a "-1*" sentence in iInput if negative.
bool Calculator::isSign(std::istringstream &istream)
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

bool Calculator::isNumber(std::istringstream &istream)
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

bool Calculator::handleInputString(std::istringstream &istream)
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

void Calculator::printInput()
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

//Removes all spaces and tabs from the string.
void Calculator::clearWhitespace(std::string &input)
{
	std::string s = "";
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ' || input[i] == '\t') {
			continue;
		}
		s += input[i];
	}
	input = s;
}

void Calculator::calculatorLoop(std::string &sInputString)
{
	clearWhitespace(sInputString);
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

void Calculator::clearVectors()
{
	iInput.clear();
	dNumbers.clear();
}

Calculator::Calculator()
{
	legalOperators = "+-*/%^pc"; // <- Must be in the same order as the constants were declared, and the operators bellow.

	int key = -1 - c_number_of_plain_const;
	operators.push_back(Operators(key--, 0, MyMath::add));
	operators.push_back(Operators(key--, 0, MyMath::sub));
	operators.push_back(Operators(key--, 1, MyMath::mul));
	operators.push_back(Operators(key--, 1, MyMath::div));
	operators.push_back(Operators(key--, 1, MyMath::mod));
	operators.push_back(Operators(key--, 2, pow, 1));
	operators.push_back(Operators(key--, 4, MyMath::nPr));
	operators.push_back(Operators(key--, 4, MyMath::nCr));

	startCalculator();
}

void Calculator::startCalculator()
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