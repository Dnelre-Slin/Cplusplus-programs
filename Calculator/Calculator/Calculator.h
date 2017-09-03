#pragma once
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
	std::unordered_map<char, Operators> m_operators;
	std::unordered_map<std::string, MathFunctions> m_functions;
	std::unordered_map<std::string, double> m_constants;
	double m_variables[26];

	bool m_do_store_variable;
	char m_variable_to_be_stored;


	double		runCalc(int start_priority, std::string &str, MyConsts &lastSymbol, int &index, int &parantheses_count);
	bool		priorityReturn(MyConsts &lastSymbol, int &start_priority, double &ans, double &multiplier);
	template <class T1, class T2>
	std::string getName(std::unordered_map<T1, T2> &map, std::string &str, int &index, int &stored_index);
	bool		handleSigns(std::string &str, int &index);
	bool		isConstant(std::string &str, int &index, double &d);
	bool		isVariable(std::string &str, int &index, double &d);
	bool		isActualNumber(std::string &str, int &index, double &d);
	bool		isNumber(std::string &str, int &index, double &d);
	void		clearWhitespace(std::string &input);
	//void		calculatorLoop(std::string sInputString, int index);
	void		initiateCalculation(std::string sInputString, int index);
public:
				Calculator();
	//void		startCalculator();
	void		calculatorLoop();
};