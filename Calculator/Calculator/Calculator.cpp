#include <iostream>
#include <string>

#include "Calculator.h"
#include "BasicMathFuncs.h"

double Calculator::runCalc(int start_priority, std::string &str, MyConsts &lastSymbol, int &index, int &parantheses_count)
{
	double ans = 0, temp_ans = 0;
	//char c;
	std::string func_name;
	int stored_index;
	while (index < str.length())
	{
		if (str[index] == '(')
		{
			double multiplier = 1;
			if (priorityReturn(lastSymbol, start_priority, ans, multiplier))
				return ans;
			parantheses_count++;
			lastSymbol = MyConsts::paranthesis_start;
			ans = multiplier * runCalc(-1, str, lastSymbol, ++index, parantheses_count);
			parantheses_count--;
			index++;
		}
		else if ((str[index] == ')') && ((lastSymbol == MyConsts::number) || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end))
		{   //If last element is a number, factorial or an end paranthesis.
			lastSymbol = MyConsts::paranthesis_end;
			if (parantheses_count < 1)
			{
				throw std::runtime_error("Syntax Error. (Too many end parantheses.)");
			}
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
				//std::cout << "variable stored in " << variable_to_be_stored <<  << ".\n";
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
		//std::cout << "par: " << parantheses_count << "      ans: " << ans << '\n';
	}
	return ans;
}

//double Calculator::runCalc(int start_priority, std::istringstream &istream, MyConsts &lastSymbol, int &parantheses_count)
//{
//	double ans = 0, temp_ans = 0;
//	char c;
//	std::string func_name;
//	std::istringstream::pos_type stream_pos;
//	while (istream.rdbuf()->in_avail() > 0)
//	{
//		c = istream.peek();
//		if (c == '(')
//		{
//			double multiplier = 1;
//			if (priorityReturn(lastSymbol, start_priority, ans, multiplier))
//				return ans;
//			//if (lastSymbol == MyConsts::number || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end) // Is a number, factorial or an end parantesis.
//			//{
//			//	if (1 > start_priority) // 1 is priority of multiply.
//			//		multiplier = ans;
//			//	else
//			//		return ans;
//			//}
//			istream >> c;
//			parantheses_count++;
//			lastSymbol = MyConsts::paranthesis_start;
//			ans = multiplier * runCalc(-1, istream, lastSymbol, parantheses_count);
//			parantheses_count--;
//			istream >> c;
//		} 
//		else if ((c == ')') && ((lastSymbol == MyConsts::number) || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end))
//		{   //If last element is a number, factorial or an end paranthesis.
//			lastSymbol = MyConsts::paranthesis_end;
//			if (parantheses_count < 1)
//			{
//				throw std::runtime_error("Syntax Error. (Too many end parantheses.)");
//			}
//			return ans;
//		}
//		else if ((c == '!') && ((lastSymbol == MyConsts::number) || (lastSymbol == MyConsts::paranthesis_end))) //If c is '!' and last element is a number or an end parathesis.
//		{
//			lastSymbol = MyConsts::factorial;
//			ans = MyMath::factorial(ans);
//			istream >> c;
//		}
//		else if ((c == '>') && ((lastSymbol == MyConsts::number) || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end))
//		{
//			istream >> c;
//			c = istream.peek();
//			if (c >= 65 && c <= 90)
//			{
//				variable_to_be_stored = c;
//				do_store_variable = true;
//				//std::cout << "variable stored in " << variable_to_be_stored <<  << ".\n";
//				istream >> c;
//				return ans;
//			}
//			throw std::runtime_error("Syntax Error. (Attempting to assign to non-variable)");
//		}
//		else if ((func_name = getName(functions, istream, stream_pos)) != "")
//		{
//			double multiplier = 1;
//			if (priorityReturn(lastSymbol, start_priority, ans, multiplier))
//			{
//				resetStream(istream, stream_pos);
//				return ans;
//			}
//			//if (lastSymbol == MyConsts::number || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end) // Is a number, factorial or an end parantesis.
//			//{
//			//	if (1 > start_priority) // 1 is priority of multiply.
//			//		multiplier = ans;
//			//	else
//			//	{
//			//		resetStream(istream, stream_pos);
//			//		return ans;
//			//	}
//			//}
//			lastSymbol = MyConsts::function;
//			ans = multiplier * functions[func_name].doOperation(runCalc(6, istream, lastSymbol, parantheses_count));
//		}
//		else if (isNumber(istream, temp_ans))
//		{
//			double multiplier = 1;
//			priorityReturn(lastSymbol, start_priority, ans, multiplier);
//			ans = multiplier * temp_ans;
//			lastSymbol = MyConsts::number;
//		}
//		else if (operators.find(c) != operators.end() && lastSymbol != MyConsts::operators && lastSymbol != MyConsts::paranthesis_start && lastSymbol != MyConsts::function)
//		{	// If c is an operator and back() is not an operator and not a '('. (Functions should also be here).
//			Operators op = operators[c];
//
//			if (op.getNextPriority() > start_priority)
//			{
//				lastSymbol = MyConsts::operators;
//				istream >> c;
//				ans = op.doOperation(ans, runCalc(op.getPriority(), istream, lastSymbol, parantheses_count));
//			}
//			else
//			{
//				return ans;
//			}
//		}
//		else if (isSign(istream))
//		{
//			lastSymbol = MyConsts::sign;
//			ans = -runCalc(6, istream, lastSymbol, parantheses_count);
//		}
//		//else if (isNumber(istream, temp_ans))
//		//{
//		//	double multiplier = 1;
//		//	priorityReturn(lastSymbol, start_priority, ans, multiplier);
//		//	//if (lastSymbol == MyConsts::paranthesis_end || lastSymbol == MyConsts::factorial)
//		//	//{	//(Should also consider variables here.)
//		//	//	ans *= temp_ans;
//		//	//}
//		//	//else
//		//	//{
//		//	//	ans = temp_ans;
//		//	//}
//		//	ans = multiplier * temp_ans;
//		//	lastSymbol = MyConsts::number;
//		//}
//		else // If it makes it this far, there must be a syntax error, since all possible legal options should be covered in the if's.
//		{
//			throw std::runtime_error("Syntax Error.");
//		}
//		//std::cout << "par: " << parantheses_count << "      ans: " << ans << '\n';
//	}
//	return ans;
//}

//double Calculator::runCalc(int start_priority, int &index)
//{
//	double ans = 0;
//	while (index < iInput.size())
//	{
//		if (iInput[index] == c_paranthesis_start)
//		{
//			ans = runCalc(-1, ++index);
//			index++;
//		}
//		else if (iInput[index] == c_paranthesis_end)
//		{
//			return ans;
//		}
//		else if (iInput[index] == c_factorial)
//		{
//			ans = MyMath::factorial(ans);
//			index++;
//		}
//		else if (iInput[index] >= 0) //Is a number.
//		{
//			ans = dNumbers[iInput[index]];
//			index++;
//		}
//		else if (iInput[index] <= operators[0].getKey() && iInput[index] >= operators[operators.size() - 1].getKey()) //Is an operator.
//		{
//			Operators op = operators[-(iInput[index] + 1 + c_number_of_plain_const)];
//			if (op.getNextPriority() > start_priority)
//			{
//				ans = op.doOperation(ans, runCalc(op.getPriority(), ++index));
//			}
//			else
//			{
//				return ans;
//			}
//		}
//		else
//		{
//			std::cout << "Should never happend!!!!!\n";
//		}
//	}
//	return ans;
//}

//int Calculator::getKeyOfOperator(char c)
//{
//	for (int i = 0; i < legalOperators.length(); i++)
//	{
//		if (c == legalOperators[i])
//		{
//			return -(i + 1 + c_number_of_plain_const);
//		}
//	}
//	return 0; // If c is not a legal operator.
//}
//
//bool Calculator::isOperator2(char c)
//{
//	for (int i = 0; i < legalOperators.length(); i++)
//	{
//		if (c == legalOperators[i])
//		{
//			return true;
//		}
//	}
//	return false;
//}
//
////Checks if a key is an operator in MyConsts.
//bool Calculator::isOperator(int key)
//{
//	if (key <= c_first_operator && key >= c_last_operator)
//	{
//		return true;
//	}
//	return false;
//}
bool Calculator::priorityReturn(MyConsts &lastSymbol, int &start_priority, double &ans, double &multiplier)
{
	if (lastSymbol == MyConsts::number || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end ) // If lastSymbol is a number, factorial or an end parantesis.
	{
		multiplier = ans;
		if (1 <= start_priority) // 1 is priority of multiply.
			return true;
	}
	return false;
}

//inline void Calculator::resetStream(std::istringstream &istream, std::istringstream::pos_type &stream_pos)
//{
//	istream.clear();
//	istream.seekg(stream_pos, istream.beg);
//}

template <class t1, class t2>
std::string Calculator::getName(std::unordered_map<t1,t2> &map, std::string &str, int &index, int &stored_index)
{
	//Solution found here.
	// https://stackoverflow.com/questions/34050729/how-to-read-from-the-same-location-in-a-stringstream-twice
	//stream_pos = istream.tellg();
	stored_index = index;
	std::string name;
	//char c = istream.peek();
	//char c2;
	while (((int)str[index] >= 97 && (int)str[index] <= 122)) // c is a small letter. Numbers represent ascii position of letters.
	{
		//istream >> c2;
		//func_name += c;
		name += str[index];
		if (map.find(name) != map.end()) // If func_name is found in functions map.
		{
			index++;
			return name;
		}
		//c = istream.peek();
		index++;
	}
	//resetStream(istream, stream_pos);
	index = stored_index;
	return "";
}

bool Calculator::isSign(std::string &str, int &index)
{
	//char c = istream.peek();
	bool is_positive = true;
	while (str[index] == '+' || str[index] == '-') {
		if (str[index] == '-') {
			is_positive = !is_positive; //Swap between positive and negative, everytime minus sign shows up
		}
		//istream >> c;
		//c = istream.peek();
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
	//std::istringstream::pos_type pos;
	int stored_index;
	std::string const_name;
	//func_name = getName(functions, istream, pos);
	const_name = getName(constants, str, index, stored_index);
	//std::cout << "Func:  \"" << func_name << "\"\n";
	//std::cout << "Const:  \"" << const_name << "\"\n";
	//if (getName(functions, istream, pos) == "" && (const_name = getName(constants, istream, pos)) != "")
	if (const_name != "")
	{
		d2 = constants[const_name];
		d *= d2;
		//std::cout << "d:  " << d << '\n';
		return true;
	}
	//resetStream(istream, pos);
	return false;
}

bool Calculator::isVariable(std::string &str, int &index, double &d)
{
	bool is_variable = false;
	double d2 = 1;
	//char c = istream.peek();
	while ((int)str[index] >= 65 && (int)str[index] <= 90) // While c is a captial letter.
	{
		d2 *= variables[(int)str[index] - 65]; // Converts from ascii capital letter to index of variables.
		//istream >> c;
		//c = istream.peek();
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
	//char c = istream.peek();
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
		//istream >> c;
		//c = istream.peek();
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
	//	while (isActualNumber(istream, d) && isVariable(istream, d) && isConstant(istream, d)) { std::cout << "WHat the fuck!!\n"; }
		return true;
	}
	return false;
}

//bool Calculator::isNumber(std::istringstream &istream, double &d)
//{
//	istream >> d;
//	if (istream.fail()) //Not a number.
//	{
//		istream.clear(); //Clear failbit.
//		return false;
//	}
//	return false;
//}
////  Gets all consecutive + and -, that are not considered operators, but signs, and reduces it to nothing, if sign is positive, or a "-1*" sentence in iInput if negative.
//bool Calculator::isSign(std::istringstream &istream)
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
//			iInput.push_back(c_multiply);
//		}
//		return true;
//	}
//	return false;
//}
//
//bool Calculator::isNumber(std::istringstream &istream)
//{
//	if (iInput.back() == c_paranthesis_end || iInput.back() == c_factorial) //Auto-places '*', if number comes right behind end paranthesis or factorial.
//	{ //(Should also consider factorial and variables here.)
//		iInput.push_back(c_multiply);
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

//bool Calculator::handleInputString(std::istringstream &istream)
//{
//	char c;
//	int op_key = 0;
//	iInput.push_back(-1); //Auto-place first start parantesis.
//	while (istream.rdbuf()->in_avail() > 0)
//	{
//		c = istream.peek();
//		if (c == '(')
//		{
//			if (iInput.back() >= 0 || iInput.back() == c_factorial || iInput.back() == c_paranthesis_end) // Is a number, factorial or an end parantesis.
//			{
//				iInput.push_back(c_multiply);
//			}
//			iInput.push_back(c_paranthesis_start);
//			istream >> c;
//		}
//		else if (c == ')' && ((iInput.back() >= 0) || iInput.back() == c_factorial || iInput.back() == c_paranthesis_end)) //Last element is a number, factorial or an end paranthesis.
//		{
//			iInput.push_back(c_paranthesis_end);
//			istream >> c;
//		}
//		else if ((c == '!') && ((iInput.back() >= 0) || (iInput.back() == c_paranthesis_end))) //If c is '!' and last element is a number or an end parathesis.
//		{
//			iInput.push_back(c_factorial);
//			istream >> c;
//		}
//		else if (isOperator(op_key = getKeyOfOperator(c)) && !isOperator(iInput.back()) && !(iInput.back() == c_paranthesis_start))
//		{// If c is an operator and back() is not an operator and not a '('. (Functions should also be here).
//			iInput.push_back(op_key);
//			istream >> c;
//		}
//		else if (isSign(istream) /* || isLetter() */ || isNumber(istream))
//		{
//			//No need for body. Everything handled in isSign, isLetter and isNumber functions.
//		}
//		else // If it makes it this far, there must be a syntax error, since all possible legal options should be covered in the if's.
//		{
//			return false; //Syntax error.
//		}
//	}
//	iInput.push_back(c_paranthesis_end); //Auto-place last end parantesis.
//	return true; //No syntax errors. Math string parsed successfully.
//}

//void Calculator::printInput()
//{
//	for (int i = 0; i < iInput.size(); i++)
//	{
//		if (iInput[i] >= 0)
//		{
//			std::cout << dNumbers[iInput[i]];
//		}
//		else
//		{
//			if (iInput[i] == c_paranthesis_start)
//			{
//				std::cout << "(";
//			}
//			else if (iInput[i] == c_paranthesis_end)
//			{
//				std::cout << ")";
//			}
//			else if (iInput[i] == c_factorial)
//			{
//				std::cout << "!";
//			}
//			else
//			{
//				std::cout << legalOperators[-(iInput[i]) - 1 - c_number_of_plain_const];
//			}
//		}
//	}
//}

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
	//std::istringstream istream(sInputString);
	try
	{
		MyConsts lastSymbol = MyConsts::paranthesis_start;
		int parantheses_count = 0, index = 0;
		double ans = runCalc(-1, sInputString, lastSymbol, index, parantheses_count);
		constants["ans"] = ans;
		if (do_store_variable)
		{
			variables[variable_to_be_stored - 65] = ans; // (- 65) to map from capital letter in ascii, to index in array.
			do_store_variable = false;
		}
		std::cout << " = " << ans << '\n';
	}
	catch (std::runtime_error re)
	{
		std::cout << re.what() << '\n';
	}
	//if (handleInputString(istream))
	//{
	//	printInput();
	//	int index = 1;
	//	try
	//	{
	//		double ans = runCalc(-1, index);
	//		std::cout << " = " << ans << '\n';
	//	}
	//	catch (std::runtime_error re)
	//	{
	//		std::cout << "Math Error. (" << re.what() << "(" << index << "))\n";
	//	}
	//}
	//else
	//{
	//	std::cout << "Syntax Error.\n";
	//}
}

//void Calculator::clearVectors()
//{
//	iInput.clear();
//	dNumbers.clear();
//}

Calculator::Calculator()
{
	//legalOperators = "+-*/%^pc"; // <- Must be in the same order as the constants were declared, and the operators bellow.

	//int key = -1 - c_number_of_plain_const;
	//operators.push_back(Operators(key--, 0, MyMath::add));
	//operators.push_back(Operators(key--, 0, MyMath::sub));
	//operators.push_back(Operators(key--, 1, MyMath::mul));
	//operators.push_back(Operators(key--, 1, MyMath::div));
	//operators.push_back(Operators(key--, 1, MyMath::mod));
	//operators.push_back(Operators(key--, 2, pow, 1));
	//operators.push_back(Operators(key--, 4, MyMath::nPr));
	//operators.push_back(Operators(key--, 4, MyMath::nCr));

	operators['+']		= Operators(0, 0, MyMath::add);
	operators['-']		= Operators(0, 0, MyMath::sub);
	operators['*']		= Operators(0, 1, MyMath::mul);
	operators['/']		= Operators(0, 1, MyMath::div);
	operators['%']		= Operators(0, 1, MyMath::mod);
	operators['^']		= Operators(0, 2, pow, 1);
	operators['v']		= Operators(0, 2, MyMath::root);
	operators['p']		= Operators(0, 4, MyMath::nPr);
	operators['c']		= Operators(0, 4, MyMath::nCr);
	operators['l']		= Operators(0, 4, MyMath::logBase);

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
	std::string sInputString;
	std::getline(std::cin, sInputString);
	while (sInputString.length() > 0) //Run till empty string is entered.
	{
		calculatorLoop(sInputString);
		//clearVectors();
		std::getline(std::cin, sInputString);
	}
}