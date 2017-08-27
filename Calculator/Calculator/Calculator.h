#pragma once
#include <vector>
#include <unordered_map>
#include <sstream>

#include "Operator.h"
#include "MyConsts.h"
#include "MathFunctions.h"

class Calculator
{
private:

	//// Some constants used to make code look more readable.
	//int const_count = 0;

	//// Plain constants
	//const int c_paranthesis_start		= --const_count;
	//const int c_paranthesis_end			= --const_count;
	//const int c_factorial				= --const_count;

	//const int c_number_of_plain_const	=  -const_count;

	//// Operator constants
	//const int c_plus					= --const_count;
	//const int c_first_operator			=   const_count;
	//const int c_minus					= --const_count;
	//const int c_multiply				= --const_count;
	//const int c_divide					= --const_count;
	//const int c_modulo					= --const_count;
	//const int c_exponential				= --const_count;
	//const int c_nPr						= --const_count;
	//const int c_nCr						= --const_count;
	//const int c_last_operator			=   const_count;

	//const int c_number_of_operators		= -const_count - c_number_of_operators;

	//// End of constant declarations. (Variable const_count, should not be used beyond this point.)

	//std::vector<int>		iInput;    //Holds mathematical sentence to be processed by runCalc method. All symbols will have negative values, and numbers will be positive.
	//std::vector<double>		dNumbers;  //Holds the actual numbers. iInput only holds index of the numbers in dNumbers. So numbers can be negative, but it's index will always be positive.
	//std::vector<Operators>	operators; //Holds all the operators to be used. Can run mathematical function directly from operator objects.

	std::unordered_map<char, Operators> operators;
	std::unordered_map<std::string, MathFunctions> functions;
	std::unordered_map<std::string, double> constants;
	double variables[26];

	bool do_store_variable;
	char variable_to_be_stored;

	//std::string legalOperators;

	double		runCalc(int start_priority, std::istringstream &istream, MyConsts &lastSymbol, int &parantheses_count);
	//double	runCalc(int start_priority, int &index);
	//int		getKeyOfOperator(char c);
	//bool	isOperator2(char c);
	//bool	isOperator(int key);
	bool		priorityReturn(MyConsts &lastSymbol, int &start_priority, double &ans, double &multiplier);
	inline void	resetStream(std::istringstream &istream, std::istringstream::pos_type &pos);
	template <class T1, class T2>
	std::string getName(std::unordered_map<T1, T2> map, std::istringstream &istream, std::istringstream::pos_type &pos);
	bool		isSign(std::istringstream &istream);
	bool		isConstant(std::istringstream &istream, double &d);
	bool		isVariable(std::istringstream &istream, double &d);
	bool		isActualNumber(std::istringstream &istream, double &d);
	bool		isNumber(std::istringstream &istream, double &d);
	//bool	isSign(std::istringstream &istream);
	//bool	isNumber(std::istringstream &istream);
	//bool	handleInputString(std::istringstream &istream);
	//void	printInput();
	void		clearWhitespace(std::string &input);
	void		calculatorLoop(std::string &sInputString);
	//void	clearVectors();
public:
				Calculator();
	void		startCalculator();
};