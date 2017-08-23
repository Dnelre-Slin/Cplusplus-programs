#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "BasicMathFuncs.h"

class Operators
{
	int key;
	int priority;
	int exp_fix;

	double(*mathFunc) (double, double);

public:
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
};

class Calculator
{
	// Some constants used to make code look more readable.
	int const_count;

	// Plain constants
	const int c_paranthesis_start;
	const int c_paranthesis_end;
	const int c_factorial;

	const int c_number_of_plain_const;

	// Operator constants
	const int c_plus;
	const int c_first_operator;
	const int c_minus;
	const int c_multiply;
	const int c_divide;
	const int c_modulo;
	const int c_exponential;
	const int c_nPr;
	const int c_nCr;
	const int c_last_operator;

	const int c_number_of_operators;

	// End of constant declarations. (Variable const_count, should not be used beyond this point.)

	std::vector<int>		iInput;    //Holds mathematical sentence to be processed by runCalc method. All symbols will have negative values, and numbers will be positive.
	std::vector<double>		dNumbers;  //Holds the actual numbers. iInput only holds index of the numbers in dNumbers. So numbers can be negative, but it's index will always be positive.
	std::vector<Operators>	operators; //Holds all the operators to be used. Can run mathematical function directly from operator objects.

	std::string legalOperators;

	double runCalc(int start_priority, int &index);
	int getKeyOfOperator(char c);
	//Checks if a key is an operator in MyConsts.
	bool isOperator(int key);
	//  Gets all consecutive + and -, that are not considered operators, but signs, and reduces it to nothing, if sign is positive, or a "-1*" sentence in iInput if negative.
	bool isSign(std::istringstream &istream);
	bool isNumber(std::istringstream &istream);
	bool handleInputString(std::istringstream &istream);
	void printInput();
	//Removes all spaces and tabs from the string.
	void clearWhitespace(std::string &input);
	void calculatorLoop(std::string &sInputString);
	void clearVectors();
	// MASTER BRANCH

public:
	Calculator();
}; 

class Calculator
{
// Some constants used to make code look more readable.
int const_count = 0;

// Plain constants
const int c_paranthesis_start = --const_count;
const int c_paranthesis_end = --const_count;
const int c_factorial = --const_count;

const int c_number_of_plain_const = -const_count;

// Operator constants
const int c_plus = --const_count;
const int c_first_operator = const_count;
const int c_minus = --const_count;
const int c_multiply = --const_count;
const int c_divide = --const_count;
const int c_modulo = --const_count;
const int c_exponential = --const_count;
const int c_nPr = --const_count;
const int c_nCr = --const_count;
const int c_last_operator = const_count;

const int c_number_of_operators = -const_count - c_number_of_operators;

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

//Removes all spaces and tabs from the string.
void clearWhitespace(std::string &input)
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

void calculatorLoop(std::string &sInputString)
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

void clearVectors()
{
	iInput.clear();
	dNumbers.clear();
}

public:
	Calculator()
	{
		legalOperators = "+-*/%^pc"; // <- Must be in the same order as the constants were declared, and the operators bellow.

		int key = -1 - c_number_of_plain_const;
		operators.push_back(Operators(key--, 0, add));
		operators.push_back(Operators(key--, 0, sub));
		operators.push_back(Operators(key--, 1, mul));
		operators.push_back(Operators(key--, 1, div));
		operators.push_back(Operators(key--, 1, mod));
		operators.push_back(Operators(key--, 2, pow, 1));
		operators.push_back(Operators(key--, 4, nPr));
		operators.push_back(Operators(key--, 4, nCr));

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

////Removes all spaces and tabs from the string.
//void clearWhitespace(std::string &input)
//{
//	std::string s = "";
//	for (int i = 0; i < input.length(); i++) {
//		if (input[i] == ' ' || input[i] == '\t') {
//			continue;
//		}
//		s += input[i];
//	}
//	input = s;
//}

/*
void insertStartEndParanthesis(std::string &input) {
	input = "(" + input + ")";
}

//Check to see if all characters are legal. Which characters that are considered legal, is determined by the string "legalCharaters".
bool checkForLegalCharacters(std::string &input) 
{
	const std::string legalCharacters = "0123456789+-*./,()";
	for (int i = 0; i < input.length(); i++) {
		bool legalFound = false;
		for (int j = 0; j < legalCharacters.length(); j++) {
			if (input[i] == legalCharacters[j]) {
				legalFound = true;
				break;
			}
		}
		if (!legalFound) {
			return false;
		}
	}
	return true;
}
*/
//Check if two or more operators are next to each other, since this is illegal. + and - can be signs, so two or 
//more of these are allowed. Returns true if everything is okay.
//bool checkForRedundantOperators(std::string &input) {
//	std::string operatorsToCheck = "*/";
//	for (int i = 0; i < input.length() - 1; i++) { 
//	//input.length() - 1 here ^, because we check the one after the index also. 
//	//Last one can't be operator anyway, since this is handled by checkForOperatorIllegalPlacement().
//		for (int j = 0; j < operatorsToCheck.length(); j++) {
//			if (input[i] == operatorsToCheck)
//		}
//	}
//}
/*
//Gets input from keyboard, using std::cin, and inserts into string called input. Input is refrence, so no need to return.
void getInput(std::string &input)
{
	input = "";
	std::cout << "Input: ";
	char c = std::cin.get();
	//Reads into char c, until end of line is reached. 
	while (c != '\n')
	{
		input += c; //Put each char from input into the string, called "input".
		c = std::cin.get();
	}
	//std::cin.getline(input, 100);
}

//Checks for any syntax error in the input string. Returns true if no errors was found.
bool checkForSyntaxErrors(std::string &input) {
	if (checkForLegalCharacters(input)) {
		return true;
	}
	return false;
}

void runCalculations(std::string &input) {

}

void runCalculator()
{
	std::string input;
	getInput(input);
	while (input.length() > 0)
	{
		clearWhitespace(input);
		insertStartEndParanthesis(input);
		if (checkForSyntaxErrors(input)) {
			//No syntax errors. Continue operations.
		}
		else {
			std::cout << "Syntax error.\n";
		}

		std::cout << "Output (" << ") : " << input << '\n';
		getInput(input);
	}
}
*/
int main()
{
	//runCalculator();
	//std::cin.get();
	//std::cin.get();

	Calculator();

	//try
	//{
	//	std::cout << nCr(50,48) << '\n';
	//}
	//catch (std::runtime_error re)
	//{
	//	std::cout << re.what() << '\n';
	//}

	system("pause");

	return 0;
}