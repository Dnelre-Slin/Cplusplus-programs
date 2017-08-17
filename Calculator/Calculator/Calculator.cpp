#include <string>
#include <iostream>

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

void insertStartEndParanthesis(std::string &input) {
	input = "(" + input + ")";
}

//Check to see if all characters are legal. Which characters that are considered legal, is determined by the string "legalCharaters".
bool checkForLegalCharacters(std::string &input) 
{
	const std::string legalCharacters = "0123456789+-*/.,()";
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

int main()
{
	runCalculator();
	//std::cin.get();
	//std::cin.get();

	return 0;
}