#include "InputHandler.h"

/*Simple method that sets the x position to the length of the string, if the old x is higher than the length of the string.*/
void InputHandler::repositionPos(std::vector<std::string> &vs, COORD &pos)
{
	if (pos.X > vs[pos.Y].length())
	{
		pos.X = vs[pos.Y].length();
	}
}

/*The int i is a number representing which key was recived using _getch in getInput. The switch-statment will handle the various allowed key-presses.*/
void InputHandler::handleInput(COORD &pos, std::vector<std::string> &vs, int i, bool &run_calculator_loop, bool &run_input_loop, bool &string_untouched)
{
	int j;
	switch (i)
	{
	case 8: //Backspace.
		if (pos.X > 0)
		{
			vs[pos.Y].erase(pos.X - 1, 1); //Backspace should erase this pos in the current string.
			pos.X -= 1;
		}
		break;
	case 13: //Enter.
		run_input_loop = false; //Stop the loop, and begin runCalc method in calculator.
		break;
	case 27: // Esc. Should stop calculator completely. Quit program.
		run_calculator_loop = false;
		run_input_loop = false;
		break;
	case 40: // (  Start_parantheses pressed. Automatically also places end paranthesis.
		vs[pos.Y].insert(vs[pos.Y].begin() + pos.X, '(');
		pos.X++;
		vs[pos.Y].insert(vs[pos.Y].begin() + pos.X, ')');
		break;
	case 0: //Not a support key, but a zero will mean that another _getch is expected, so it is called here.
		_getch();
		break;
	case 224:
		j = _getch(); //Same as with zero, 244 needs another _getch call.
		if (j == 75 && pos.X > 0) // Left arrow key.
		{
			pos.X = pos.X - 1; //Move pos on to the left.
		}
		else if (j == 77 && pos.X < vs[pos.Y].length()) //Right arrow key.
		{
			pos.X = pos.X + 1; //Move pos one to the right.
		}
		else if (j == 72 && pos.Y > 0) // Up arrow key.
		{
			pos.Y--; //Moves pos one up.
			repositionPos(vs, pos);
		}
		else if (j == 80 && pos.Y < vs.size() - 1) // Down arrow key.
		{
			pos.Y++; //Moves pos one down.
			repositionPos(vs, pos);
		}
		else if (j == 83 && pos.X < vs[pos.Y].length()) //Delete.
		{
			vs[pos.Y].erase(pos.X, 1); //Delete, removes char at next pos, and does not move pos.
		}
		break;
	default:
		if (string_untouched && (i == 33 || i == 43 || i == 45 || i == 42 || i == 47 || i == 94)) // If i is ! + - * / ^
		{
			vs[pos.Y] = vs[pos.Y].substr(0, pos.X) + "ans" + (char)i + vs[pos.Y].substr(pos.X); //Automatically places ans, if an operator is the first thing pressed in a new expression.
			pos.X += 4; //Move 4, 3 for ans, and 1 for the operator.
		}
		else if (i >= 32 && i <= 126) //Regular symbols. Should be places into the current pos in the string.
		{
			vs[pos.Y].insert(vs[pos.Y].begin() + pos.X, (char)i);
			pos.X += 1;
		}
	}
	string_untouched = false; //String no longer untouched. After this, ans will not be places automatically when operator is pressed.
}

/*Method that clears the entire choosen line in the console window.*/
void InputHandler::clearLine(int line)
{
	setCursorPosition(0, line);
	std::cout << "                                                                     ";
	setCursorPosition(0, line);
}

/*Used to get prettier code. setCursorPosition looks better than SetConsoleCursorPosition(Handle) and so forth.*/
inline void InputHandler::setCursorPosition(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)x, (short)y });
}

/*Get and handle user input.*/
int InputHandler::getInput(std::vector<std::string> &strings, bool &run_calculator_loop)
{
	if (!strings.back().empty()) // If last string in vector is not empty.
	{
		strings.push_back(""); // Add a new empty string to vector.
	}
	bool run_input_loop = true, string_untoched = true;
	int i = 0;
	COORD pos = { 0, (strings.size() - 1) }; //Put cursor start position to X = 0, and Y = (last index in string vector).
	while (run_input_loop) //Run until enter or esc is pressed.
	{
		setCursorPosition(pos.X, pos.Y * 2); //Set pos to current pos. Times 2 on Y, to have alternate lines of expressions and answers.
		i = _getch(); //Get user keypress.
		handleInput(pos, strings, i, run_calculator_loop, run_input_loop, string_untoched);
		setCursorPosition(0, pos.Y * 2); //Set CursorPosition X to 0, before rewriting the string.
		std::cout << strings[pos.Y] << " "; //Rewrite string.
	}
	return pos.Y; //Return index of string that user pressed enter on.
}