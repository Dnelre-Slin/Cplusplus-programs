#include <iostream>
#include <string>

#include "Calculator.h"
#include "BasicMathFuncs.h"
#include "InputHandler.h"

/*Method that parses string and imidietly run calculatorions on it.
str holds the math-equation enter by the user. index points at the right place in str. 
parantheses_count is used to make sure there are never more end parentheses than start parentheses.
lastSymbol is the previous symbol in the string. start_priority is used to handle the priority of differant math operators.
If priority of next operator is higher than start_priority, runCalc will be recursivly called. Else, the method will return.*/
double Calculator::runCalc(int start_priority, std::string &str, MyConsts &lastSymbol, int &index, int &parantheses_count)
{
    //Ans stores the answer so far calculated in the string. Temp_ans is passed by reference to some methods.
	double ans = 0, temp_ans = 0; 
	std::string func_name; //Passed by reference to getName, to check if the string is a legal mathematical function name.
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
		{   /*The current char is an end_paranthesis. lastSymbol must also be number, factorial or an other end paranthesis,
			or there will be a syntax error be the user. Something like "(2+3*)" should not be allowed.*/
			lastSymbol = MyConsts::paranthesis_end; 
			if (parantheses_count < 1)
			{//Throw exception if there are more end parantheses than start parantheses.
				throw std::runtime_error("Syntax Error. (Too many end parantheses.)"); 
			}
			/*Index is not increased in this method. This means that when this method returns, the last call on the stack will also
			have ')' as the next char. This will cause all call's to return. However, in the start paranthesis condition above, 
			the index is increased under the recursive call. This will mean that all recursive calls will be returned until the
			start parantheses is reached. This way, the entire paranthesis expression will be calculated, and returned as one number.
			The parantheses_count is also decreased in the start paranthesis method, to ensure that it will only decrease once per
			end paranthesis.*/
			return ans;
		}
		else if ((str[index] == '!') && ((lastSymbol == MyConsts::number) || (lastSymbol == MyConsts::paranthesis_end)))
		{ //If current char is the factorial symbol. Also check for syntax errors. Only a number or a parantheses expression should be in front of a factorial symbol.
			lastSymbol = MyConsts::factorial;
			ans = MyMath::factorial(ans); //ans becomes the factorial of what is was.
			index++;
		}
		else if ((str[index] == '>') && ((lastSymbol == MyConsts::number) || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end))
		{// '>' symbol is used to store value in a variable. Must come after number, factorial or end paranthesis, or syntax error should be thrown.
			if ((++index == str.length() -1) && (str[index] >= 65 && str[index] <= 90)) //Ascii table values between 65 and 90 are lower case english alfabet letters.
			{ //Only a capital letter can come after '>', since these are the variables. Can only assign to one variable, so only one char must be left in the string.
				m_variable_to_be_stored = str[index];
				m_do_store_variable = true; //Sets to true, to indicate that a variable should be stored after the runCalc method is finised.
				index++;
				return ans;
			}
			throw std::runtime_error("Syntax Error. (Attempting to assign to non-variable)");
		}
		else if ((func_name = getName(m_functions, str, index, stored_index)) != "")
		{/*Condition to check if the next few char's is one of the math functions supported be the calculator. Get name will return an empty string if function name not found in m_functions map.
		 If name is found, it will be stored in func_name. stored_index will store where index was before getName call. Can be used to reset index if necessary.*/
			double multiplier = 1;
			if (priorityReturn(lastSymbol, start_priority, ans, multiplier))
			{ //Like with paranthesis start, this will make something like "2tan(45)" legal, and treat it like "2*tan(45)".
				index = stored_index; // If method must return, the index is reset, so that the math function will be treated later, and not skipped all together.
				return ans;
			}
			lastSymbol = MyConsts::function;
			ans = multiplier * m_functions[func_name].doOperation(runCalc(6, str, lastSymbol, index, parantheses_count));
			//Get the right math function from the map, and do it's operation on the result of a recursive call to runCalc. Start_priority is 6, so that it should return before all operators.
		}
		else if (isNumber(str, index, temp_ans))
		{ //Is number check if next few symbols in str is a variable(A,B), a constant(pi,e), or an actual number(4,-2.5).
			double multiplier = 1;
			priorityReturn(lastSymbol, start_priority, ans, multiplier); //Never needs to return, but might change multiplier.
			ans = multiplier * temp_ans; //Temp_ans was set in isNumber method call. multiplier might have changed in priorityReturn call.
			lastSymbol = MyConsts::number;
		}
		else if (m_operators.find(str[index]) != m_operators.end() && lastSymbol != MyConsts::operators && lastSymbol != MyConsts::paranthesis_start && lastSymbol != MyConsts::function)
		{	/*Checks if current symbol in str is an operator, that is supported be the calculator. If it is found in the m_operators map, it will be a legal operator.
			Also needs to check if it is preceded be a symbol that it should not be allowed to come after. "(*3)" should not be allowed. Neither should "(3**4)". This will also mean that 
			"(2+-3)" or "(2*-4) is also not allowed. The isSign condition below will deal with this." */
			Operators op = m_operators[str[index]]; //Gets the operator in the m_operators map, and stores it in op.

			if (op.getNextPriority() > start_priority)
			{//If the op's priority is higher than the start_priority, it should recursive call.
				lastSymbol = MyConsts::operators;
				index++;
				ans = op.doOperation(ans, runCalc(op.getPriority(), str, lastSymbol, index, parantheses_count));
				/*Do operation of op, on ans and result of recursive call to runCalc. Start_priority of call should be the same as op's priority. This way, it will return when lower
				priority is found. Plus and minus has lower priority than multiply and divide. So it will do multiplies and divitions before pluses and minuses.*/
			}
			else
			{
				return ans; //Return if the priority of op is same or lower than start_priority.
			}
		}
		else if (str[index] == '+' || str[index] == '-')
		{//Handles signs. If (2+-3) is entered be user, the first +, will be treaded as an operator. The minus will not, since it is preceded be an illegal char. 
			if (handleSigns(str, index)) //(2+-+-+-+----++----3) will be treated as (2+-3). 
			{//handleSigns will reduce an any length chain of signs, down to a positive or negative sign. If it is positive, nothing needs to happend. If it is negative, look at next comment.
				lastSymbol = MyConsts::sign;
				ans = -runCalc(6, str, lastSymbol, index, parantheses_count);// If negative, place a minus in front of recursive call, and get next number or paranthesis, and negate it.
			}
		}
		else // If it makes it this far, there must be a syntax error, since all possible legal options should be covered in the if's above.
		{
			throw std::runtime_error("Syntax Error.");
		}
	}
	return ans;
}

//Method that checks whether an implicit multiply call should return or not. Implicit multiply means something like this "3(2+2)". Between 3 and (, there is an implicit multiply.
bool Calculator::priorityReturn(MyConsts &lastSymbol, int &start_priority, double &ans, double &multiplier)
{
	if (lastSymbol == MyConsts::number || lastSymbol == MyConsts::factorial || lastSymbol == MyConsts::paranthesis_end) // If lastSymbol is a number, factorial or an end parantesis.
	{//If lastSymbol is not a number, factorial or an end paranthesis, there is no implicit multiply. Example: "(4+(5-3))" There is an operator between 4 and (, therefor not an implicit multiply.
		multiplier = ans; //multiplier should not be 1 now, but what ans was.
		if (1 <= start_priority) // 1 is priority of multiply.
			return true;
	}
	return false;
}

/*This method checks if the next few chars in str match a key in the given map. Template used to allow for both functions-map and constants-map.
If name is found, it will be returned. If not, the index will jump back to stored_index, and an empty string will be returned.*/
template <class t1, class t2>
std::string Calculator::getName(std::unordered_map<t1, t2> &map, std::string &str, int &index, int &stored_index)
{
	stored_index = index; //Stores where the index was before searching for a name in str.
	std::string name;
	while (((int)str[index] >= 97 && (int)str[index] <= 122)) // Keep looking at next char in str until the char is not a lower case letter(Ascii positions 97-122 are lower case letters).
	{
		name += str[index]; //Name started as an empty string, and will append every char that is a lower case letter.
		if (map.find(name) != map.end()) // Checks if name is a key in the map. If it is, returns name.
		{
			index++;
			return name;
		}
		index++;
	}
	index = stored_index; //At this point, the sequence of lower case letters, if any, was not a supported function or constant name. Index is therefore restored to its stored position.
	return ""; //Returns empty string to indicate that name was not found.
}

/*Method that reduces a sequence of concurrent pluses and minuses, to a boolean representation of whether the following number or expression should be positive or negative.*/
bool Calculator::handleSigns(std::string &str, int &index)
{
	bool is_positive = true;
	while (str[index] == '+' || str[index] == '-') { //Runs through sequence of pluses and minuses.
		if (str[index] == '-') { //Everytime a minus is found, the bool is_positive will swap.
			is_positive = !is_positive;
		}
		index++;
	}
	if (!is_positive)
	{
		return true; //If is_positive is false, i.e. the following number or expression should be negative, true is returned.
	}
	return false;
}

/*Check whether the following char in str is one of the supported mathematical constants.*/
bool Calculator::isConstant(std::string &str, int &index, double &d)
{
	double d2;
	int stored_index;
	std::string const_name;
	const_name = getName(m_constants, str, index, stored_index); //Used getName method to find a constant name.
	if (const_name != "") //If const_name is not an empty string, the name was found.
	{
		d2 = m_constants[const_name]; //Store the value of this constant, be using name as key in the constants-map, in the double d2.
		d *= d2; //d will be updated with the d2 value. Since d was passed be reference, it will be changed where this method was called from.
		return true; //Return true to indicate a constant was found in str.
	}
	return false;
}

/*This method looks for variables in str, and updates d with the value currently stored in this variable.*/
bool Calculator::isVariable(std::string &str, int &index, double &d)
{
	bool is_variable = false;
	double d2 = 1;
	while ((int)str[index] >= 65 && (int)str[index] <= 90) // While c is a captial letter. Takes all consecutive variables in str.
	{
		d2 *= m_variables[(int)str[index] - 65]; // Converts from ascii capital letter to index of m_variables.
		index++;
		is_variable = true; //Indicates that a variable was found in str.
	}
	d *= d2;
	return is_variable;
}

/*Method that checks if the next few chars in str are digits, and casts all of them to a single double value.*/
bool Calculator::isActualNumber(std::string &str, int &index, double &d)
{
	double d2;
	bool decimal_point_used = false; //Used to check if a decimal point has already appeared in this number.
	std::string nr;
	while (str[index] == '.' || str[index] == ',' || ((int)str[index] >= 48 && (int)str[index] <= 57)) // While c is a . or a , or a number.
	{
		if ((str[index] == '.' || str[index] == ',') && decimal_point_used) //If a decimal point is found, and one is in the number already, throw an exception.
			throw std::runtime_error("Syntax Error. (Two or more decimal points in one number)");
		if (str[index] == ',' || str[index] == '.') //Both , and . are acceptable as decimal points.
		{
			nr += '.'; //Add a decimal point to the nr-string.
			decimal_point_used = true; //Indicate that a decimal point has been used in number.
		}
		else
			nr += str[index]; //If not a . or a , the next char must be a digit, because of the condition in the while loop expression. So append this digit to nr-string.
		index++;
	}
	if (nr.length() > 0) //If nr.length is greater than 0, a number can be made using stds stod function.
	{
		d2 = std::stod(nr);
		d *= d2;
		return true;
	}
	return false;
}

/*Method that checks if the next few chars in str is a variable, a constant, or an actual number.*/
bool Calculator::isNumber(std::string &str, int &index, double &d)
{
	d = 1;
	if (isActualNumber(str, index, d) || isVariable(str, index, d) || isConstant(str, index, d)) //If one or more of these are true, a number was found and true will be returned.
	{// d starts of as one, and will be multiplied with the answer of each method. This happends at the end of each of these 3 methods.
		return true;
	}
	return false;
}

/*Removes all spaces and tabs from the string.*/
void Calculator::clearWhitespace(std::string &input)
{
	std::string s = ""; //Makes a new string, and copies each element from input string.
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ' || input[i] == '\t') { //Every element except for space and tab will be added. This way, no whitespace will be copied over.
			continue;
		}
		s += input[i];
	}
	input = s; //Input becomes itself, without whitespace.
}

/*Prepare program and console window for runCalc call.*/
void Calculator::initiateCalculation(std::string sInputString, int index)
{
	InputHandler::setCursorPosition(0, (index * 2 + 1)); //Sets cursor position to write result.
	InputHandler::clearLine(index * 2 + 1); //Clears line where result should be written.
	clearWhitespace(sInputString); //Removes whitespace from string.
	if (sInputString.empty())//If input string is empty (will also be the case if string only consists of whitespace), return immediately, without running runCalc.
		return;
	try //Try-catch to handle exceptions.
	{
		MyConsts lastSymbol = MyConsts::paranthesis_start; //Initate lastSymbol as paranthesis start. This will make the most sense for the runCalc function.
		int parantheses_count = 0, index = 0;
		double ans = runCalc(-1, sInputString, lastSymbol, index, parantheses_count); //Run runCalc, and store answer in the double ans.
		if (lastSymbol != MyConsts::paranthesis_end && lastSymbol != MyConsts::factorial && lastSymbol != MyConsts::number)
			throw std::runtime_error("Syntax error."); //If lastSymbol is not a legal end-of-expression character, throw a syntax error.
		m_constants["ans"] = ans; //Store result in ans constant. This way ans will always be the result of the last runCalc operation.
		if (m_do_store_variable) //If a store variable was found while parsing string in runCalc, store result in the set variable.
		{
			m_variables[m_variable_to_be_stored - 65] = ans; // (- 65) to map from capital letter in ascii, to index in array. If 'A' is variable to be used, it will be stored at index 0.
			m_do_store_variable = false; //Resets bool.
		}
		std::cout << "\t\t\t\t = " << ans; //Use some tabs, to get answer a little further in on the console window.
	}
	catch (std::runtime_error re)
	{
		std::cout << "\t\t" << re.what(); //Cout what the error was.
	}
}

Calculator::Calculator()
{
	//m_operators holds all the supported operators for this calculator. Just add here, if more operators should be supported.
	m_operators['+']		= Operators(0, MyMath::add);
	m_operators['-']		= Operators(0, MyMath::sub);
	m_operators['*']		= Operators(1, MyMath::mul);
	m_operators['/']		= Operators(1, MyMath::div);
	m_operators['%']		= Operators(1, MyMath::mod);
	m_operators['^']		= Operators(2, pow, 1);
	m_operators['v']		= Operators(2, MyMath::root);
	m_operators['p']		= Operators(4, MyMath::nPr);
	m_operators['c']		= Operators(4, MyMath::nCr);
	m_operators['l']		= Operators(4, MyMath::logBase);

	//m_functions holds supported functions. Same as above, adding here will allow more functions to be supported by calculator.
	m_functions["tan"]		= MathFunctions(tan);
	m_functions["sin"]		= MathFunctions(sin);
	m_functions["cos"]		= MathFunctions(cos);
	m_functions["atan"]		= MathFunctions(atan);
	m_functions["asin"]		= MathFunctions(asin);
	m_functions["acos"]		= MathFunctions(acos);
	m_functions["sqrt"]		= MathFunctions(sqrt);
	m_functions["ln"]		= MathFunctions(log);
	m_functions["log"]		= MathFunctions(log10);
	m_functions["abs"]		= MathFunctions(abs);

	//Constants also stored in a map.
	m_constants["ans"]		= 0;
	m_constants["pi"]		= 3.1415926535897932384626433832795028841971693993751;
	m_constants["e"]		= 2.718281828459045235360287471352662497757247;

	//Variables to handle calculator-variables. Both initiated to false and 0.
	m_do_store_variable		= false; 
	m_variable_to_be_stored = '0';

	for (int i = 0; i < 26; i++) // 26 is the number of captial letters in the english alfabet. Capital letters are used to store variables.
	{
		m_variables[i]		= 0; // Initialize all variables to zero.
	}

	calculatorLoop(); //Run calculator loop.
}

/*Main loop for calculator. Runs until user presses 'esc'-key. Will alternate between getting user input, and running calculations.*/
void Calculator::calculatorLoop()
{
	std::vector<std::string> strings; //Vector that holds all math expressions entered. This allowes user to go back up, and change previously entered expressions.
	strings.push_back(""); //Initiate vector strings, with one empty string.
	bool run_calculator_loop = true;
	int index = InputHandler().getInput(strings, run_calculator_loop); //Get input from user, using InputHandler class. 
	//Index is the index in strings-vector, of the string the user was highlighted on, while pressing the 'enter'-key.
	while (run_calculator_loop) //Run till 'esc'-key is pressed. InputHandler will set this bool to false if esc is pressed.
	{
		for (int i = index; i < strings.size(); i++)
		{ //Run through all strings, after and including the value of index. This will make all expressions below a changed one, also update.
			initiateCalculation(strings[i], i); 
		}
		index = InputHandler().getInput(strings, run_calculator_loop);
	}
}