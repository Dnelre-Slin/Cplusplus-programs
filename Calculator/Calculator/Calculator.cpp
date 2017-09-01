#include <iostream>
#include <string>

#include "Calculator.h"
#include "BasicMathFuncs.h"
#include "InputHandler.h"

//Method that parses string and imidietly run calculatorions on it.
//str holds the math-equation enter by the user. index points at the right place in str. 
//parantheses_count is used to make sure there are never more end parentheses than start parentheses.
//lastSymbol is the previous symbol in the string. start_priority is used to handle the priority of differant math operators.
//If priority of next operator is higher than start_priority, runCalc will be recursivly called. Else, the method will return.
double Calculator::runCalc(int start_priority, std::string &str, MyConsts &lastSymbol, int &index, int &parantheses_count)
{
    //Ans stores the answer so far calculated in the string. Temp_ans is passed by reference to some methods.
	double ans = 0, temp_ans = 0; 
	std::string func_name; //Passed by reference to getName, to check if the string is a legal matematical function name.
	int stored_index; //Used so that index can jump back, if it goes to far in some cases.
	while (index < str.length()) //Run while index is inbounds of str.
	{
		if (str[index] == '(') // If current char is start paranthesis.
		{
			double multiplier = 1; //Used if user enters something like "2(3+4)" to treat the lack of an operator as a multipy.
			if (priorityReturn(lastSymbol, start_priority, ans, multiplier))//Checks if priority is lower or higher than start_priority.
				return ans;
			parantheses_count++; //One start paranthesis means that paratheses_count should increase.
			lastSymbol = MyConsts::paranthesis_start; //Set last symbol to parathesis_start.
			ans = multiplier * runCalc(-1, str, lastSymbol, ++index, parantheses_count); //index increased in call.
			//Reqursive calls runCalc, with -1 start_priority. This way, it will only return when an end_paranthesis is found.
			parantheses_count--;//Parantheses_count reduced here, instead of in the ')' condition. Explained below.
			index++; //Increase index again. Also explained below.
		}
		else if ((str[index] == ')') && ((lastSymbol == MyConsts::number) || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end))
		{   //The current char is an end_paranthesis. lastSymbol must also be number, factorial or an other end paranthesis,
			//or there will be a syntax error be the user. Something like "(2+3*)" should not be allowed.
			lastSymbol = MyConsts::paranthesis_end; 
			if (parantheses_count < 1)
			{//Throw exception if there are more end parantheses than start parantheses.
				throw std::runtime_error("Syntax Error. (Too many end parantheses.)"); 
			}
			/*Index is not increased in this method. This means that when this method returns, the last call on the stack will also
			have ')' as the next char. This will cause all call's to return. However, in the start paranthesis condition above, 
			the index is increased under the recursive call. This will mean that all recursive calls will be returned until the
			start parantheses is reached. This way, the entire paranthesis expretion will be calculated, and returned as one number.
			The parantheses_count is also decreased in the start paranthesis method, to ensure that it will only decrease once per
			end paranthesis.*/
			return ans;
		}
		else if ((str[index] == '!') && ((lastSymbol == MyConsts::number) || (lastSymbol == MyConsts::paranthesis_end))) //If c is '!' and last element is a number or an end parathesis.
		{
			lastSymbol = MyConsts::factorial;
			ans = MyMath::factorial(ans);
			index++;
		}
		else if ((str[index] == '>') && ((lastSymbol == MyConsts::number) || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end))
		{
			if (str[++index] >= 65 && str[index] <= 90)
			{
				variable_to_be_stored = str[index];
				do_store_variable = true;
				index++;
				return ans;
			}
			throw std::runtime_error("Syntax Error. (Attempting to assign to non-variable)");
		}
		else if ((func_name = getName(functions, str, index, stored_index)) != "")
		{
			double multiplier = 1;
			if (priorityReturn(lastSymbol, start_priority, ans, multiplier))
			{
				index = stored_index; // Reset index to index_pos.
				return ans;
			}
			lastSymbol = MyConsts::function;
			ans = multiplier * functions[func_name].doOperation(runCalc(6, str, lastSymbol, index, parantheses_count));
		}
		else if (isNumber(str, index, temp_ans))
		{
			double multiplier = 1;
			priorityReturn(lastSymbol, start_priority, ans, multiplier);
			ans = multiplier * temp_ans;
			lastSymbol = MyConsts::number;
		}
		else if (operators.find(str[index]) != operators.end() && lastSymbol != MyConsts::operators && lastSymbol != MyConsts::paranthesis_start && lastSymbol != MyConsts::function)
		{	// If c is an operator and back() is not an operator and not a '('. (Functions should also be here).
			Operators op = operators[str[index]];

			if (op.getNextPriority() > start_priority)
			{
				lastSymbol = MyConsts::operators;
				index++;
				ans = op.doOperation(ans, runCalc(op.getPriority(), str, lastSymbol, index, parantheses_count));
			}
			else
			{
				return ans;
			}
		}
		else if (str[index] == '+' || str[index] == '-')
		{
			if (isSign(str, index))
			{
				lastSymbol = MyConsts::sign;
				ans = -runCalc(6, str, lastSymbol, index, parantheses_count);
			}
		}
		else // If it makes it this far, there must be a syntax error, since all possible legal options should be covered in the if's.
		{
			throw std::runtime_error("Syntax Error.");
		}
	}
	return ans;
}

bool Calculator::priorityReturn(MyConsts &lastSymbol, int &start_priority, double &ans, double &multiplier)
{
	if (lastSymbol == MyConsts::number || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end) // If lastSymbol is a number, factorial or an end parantesis.
	{
		multiplier = ans;
		if (1 <= start_priority) // 1 is priority of multiply.
			return true;
	}
	return false;
}

template <class t1, class t2>
std::string Calculator::getName(std::unordered_map<t1, t2> &map, std::string &str, int &index, int &stored_index)
{
	stored_index = index;
	std::string name;
	while (((int)str[index] >= 97 && (int)str[index] <= 122)) // c is a small letter. Numbers represent ascii position of letters.
	{
		name += str[index];
		if (map.find(name) != map.end()) // If func_name is found in functions map.
		{
			index++;
			return name;
		}
		index++;
	}
	index = stored_index;
	return "";
}

bool Calculator::isSign(std::string &str, int &index)
{
	bool is_positive = true;
	while (str[index] == '+' || str[index] == '-') {
		if (str[index] == '-') {
			is_positive = !is_positive; //Swap between positive and negative, everytime minus sign shows up.
		}
		index++;
	}
	if (!is_positive)
	{
		return true;
	}
	return false;
}

bool Calculator::isConstant(std::string &str, int &index, double &d)
{
	double d2;
	int stored_index;
	std::string const_name;
	const_name = getName(constants, str, index, stored_index);
	if (const_name != "")
	{
		d2 = constants[const_name];
		d *= d2;
		return true;
	}
	return false;
}

bool Calculator::isVariable(std::string &str, int &index, double &d)
{
	bool is_variable = false;
	double d2 = 1;
	while ((int)str[index] >= 65 && (int)str[index] <= 90) // While c is a captial letter.
	{
		d2 *= variables[(int)str[index] - 65]; // Converts from ascii capital letter to index of variables.
		index++;
		is_variable = true;
	}
	d *= d2;
	return is_variable;
}

bool Calculator::isActualNumber(std::string &str, int &index, double &d)
{
	double d2;
	bool decimal_point_used = false;
	std::string nr;
	while (str[index] == '.' || str[index] == ',' || ((int)str[index] >= 48 && (int)str[index] <= 57)) // While c is a . or a , or a number.
	{
		if ((str[index] == '.' || str[index] == ',') && decimal_point_used)
			throw std::runtime_error("Syntax Error. (Two or more decimal points in one number)");
		if (str[index] == ',' || str[index] == '.')
		{
			nr += '.';
			decimal_point_used = true;
		}
		else
			nr += str[index];
		index++;
	}
	if (nr.length() > 0)
	{
		d2 = std::stod(nr);
		d *= d2;
		return true;
	}
	return false;
}

bool Calculator::isNumber(std::string &str, int &index, double &d)
{
	d = 1;
	if (isActualNumber(str, index, d) || isVariable(str, index, d) || isConstant(str, index, d))
	{
		return true;
	}
	return false;
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

void Calculator::calculatorLoop(std::string sInputString, int index)
{
	clearWhitespace(sInputString);
	if (sInputString.empty())
		return;
	InputHandler::setCursorPosition(0, (index * 2 + 1));
	InputHandler::clearLine(index * 2 + 1);
	try
	{
		MyConsts lastSymbol = MyConsts::paranthesis_start;
		int parantheses_count = 0, index = 0;
		double ans = runCalc(-1, sInputString, lastSymbol, index, parantheses_count);
		if (lastSymbol != MyConsts::paranthesis_end && lastSymbol != MyConsts::factorial && lastSymbol != MyConsts::number)
			throw std::runtime_error("Syntax error.");
		constants["ans"] = ans;
		if (do_store_variable)
		{
			variables[variable_to_be_stored - 65] = ans; // (- 65) to map from capital letter in ascii, to index in array.
			do_store_variable = false;
		}
		//InputHandler::setCursorPosition(0,index * 2 - 1);
		std::cout << "\t\t\t\t = " << ans;
	}
	catch (std::runtime_error re)
	{
		std::cout << "\t\t" << re.what();
	}
}

Calculator::Calculator()
{
	operators['+']		= Operators(0, MyMath::add);
	operators['-']		= Operators(0, MyMath::sub);
	operators['*']		= Operators(1, MyMath::mul);
	operators['/']		= Operators(1, MyMath::div);
	operators['%']		= Operators(1, MyMath::mod);
	operators['^']		= Operators(2, pow, 1);
	operators['v']		= Operators(2, MyMath::root);
	operators['p']		= Operators(4, MyMath::nPr);
	operators['c']		= Operators(4, MyMath::nCr);
	operators['l']		= Operators(4, MyMath::logBase);

	functions["tan"]	= MathFunctions(tan);
	functions["sin"]	= MathFunctions(sin);
	functions["cos"]	= MathFunctions(cos);
	functions["atan"]	= MathFunctions(atan);
	functions["asin"]	= MathFunctions(asin);
	functions["acos"]	= MathFunctions(acos);
	functions["sqrt"]	= MathFunctions(sqrt);
	functions["ln"]		= MathFunctions(log);
	functions["log"]	= MathFunctions(log10);
	functions["abs"]	= MathFunctions(abs);


	constants["ans"]	= 0;
	constants["pi"]		= 3.1415926535897932384626433832795028841971693993751;
	constants["e"]		= 2.718281828459045235360287471352662497757247;

	do_store_variable = false;
	variable_to_be_stored = '0';

	for (int i = 0; i < 26; i++) // 26 is the number of captial letters in the english alfabet. Capital letters are used to store variables.
	{
		variables[i] = 0; // Initialize all variables to zero.
	}

	startCalculator();
}

void Calculator::startCalculator()
{
	std::vector<std::string> strings;
	strings.push_back("");
	bool run_calculator_loop = true;
	//std::string sInputString;
	//std::getline(std::cin, sInputString);
	int index = InputHandler().getInput(strings, run_calculator_loop);
	while (run_calculator_loop) //Run till empty string is entered.
	{
		for (int i = index; i < strings.size(); i++)
		{
			calculatorLoop(strings[i], i);
		}
		//std::getline(std::cin, sInputString);
		index = InputHandler().getInput(strings, run_calculator_loop);
	}
}