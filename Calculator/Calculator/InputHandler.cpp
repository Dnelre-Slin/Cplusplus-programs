#include "InputHandler.h"

//inline void InputHandler::writeToString(std::string &s, COORD &pos, char c)
//{
//	s = s.substr(0, pos.X) + c + s.substr(pos.X);
//}
//
//void removeFromString(std::string &s, COORD &pos)
//{
//	s.erase(pos.X - 1, 1);
//}

void InputHandler::repositionPos(std::vector<std::string> &vs, COORD &pos)
{
	if (pos.X > vs[pos.Y].length())
	{
		pos.X = vs[pos.Y].length();
	}
}

void InputHandler::handleInput(COORD &pos, std::vector<std::string> &vs, int i, bool &run_calculator_loop, bool &run_input_loop, bool &string_untouched)
{
	int j;
	switch (i)
	{
	case 8: //Backspace.
		if (pos.X > 0)
		{
			vs[pos.Y].erase(pos.X - 1, 1);
			pos.X -= 1;
		}
		break;
	case 13: //Enter.
		run_input_loop = false;
		break;
	case 27: // Esc.
		run_calculator_loop = false;
		run_input_loop = false;
		break;
	case 40: // (  Start_parantheses.
		vs[pos.Y].insert(vs[pos.Y].begin() + pos.X, '(');
		pos.X++;
		vs[pos.Y].insert(vs[pos.Y].begin() + pos.X, ')');
		break;
	case 0:
		_getch();
		break;
	case 224:
		j = _getch();
		if (j == 75 && pos.X > 0) // Left arrow key.
		{
			pos.X = pos.X - 1;
		}
		else if (j == 77 && pos.X < vs[pos.Y].length()) //Right arrow key.
		{
			pos.X = pos.X + 1;
		}
		else if (j == 72 && pos.Y > 0) // Up arrow key.
		{
			pos.Y--;
			repositionPos(vs, pos);
		}
		else if (j == 80 && pos.Y < vs.size() - 1) // Down arrow key.
		{
			pos.Y++;
			repositionPos(vs, pos);
		}
		else if (j == 83 && pos.X < vs[pos.Y].length()) //Delete.
		{
			vs[pos.Y].erase(pos.X, 1);
		}
		break;
	default:
		if (string_untouched && (i == 33 || i == 43 || i == 45 || i == 42 || i == 47 || i == 94)) // If i is ! + - * / ^
		{
			vs[pos.Y] = vs[pos.Y].substr(0, pos.X) + "ans" + (char)i + vs[pos.Y].substr(pos.X);
			pos.X += 4;
		}
		else if (i >= 32 && i <= 126)
		{
			vs[pos.Y].insert(vs[pos.Y].begin() + pos.X, (char)i);
			pos.X += 1;
		}
	}
	string_untouched = false;
}

void InputHandler::clearLine(int line)
{
	setCursorPosition(0, line);
	std::cout << "                                                                     ";
	setCursorPosition(0, line);
}

inline void InputHandler::setCursorPosition(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)x, (short)y });
}

int InputHandler::getInput(std::vector<std::string> &strings, bool &run_calculator_loop)
{
	if (!strings.back().empty()) // If last string in vector is not empty.
	{
		strings.push_back(""); // Add a new empty string to vector.
	}
	bool run_input_loop = true, string_untoched = true;
	int i = 0;
	COORD pos = { 0, (strings.size() - 1) }; //Put cursor start position to X = 0, and Y = (last string in vector's index * 2). * 2 is to skip the answer lines in the console.
	while (run_input_loop)
	{
		setCursorPosition(pos.X, pos.Y * 2);
		i = _getch();
		handleInput(pos, strings, i, run_calculator_loop, run_input_loop, string_untoched);
		setCursorPosition(0, pos.Y * 2);
		std::cout << strings[pos.Y] << " ";
	}
	return pos.Y;
}