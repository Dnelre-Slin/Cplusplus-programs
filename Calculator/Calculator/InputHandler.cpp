#include "InputHandler.h"

inline void writeToString(std::string &s, COORD &pos, char c)
{
	s = s.substr(0, pos.X) + c + s.substr(pos.X);
}

void removeFromString(std::string &s, COORD &pos)
{
	s.erase(pos.X - 1, 1);
}

void repositionPos(std::vector<std::string> &vs, COORD &pos)
{
	if (pos.X > vs[pos.Y].length())
	{
		pos.X = vs[pos.Y].length();
	}
}

void handleInput(COORD &pos, std::vector<std::string> &vs, int i)
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
		vs.insert(vs.begin() + ++pos.Y, "");
		pos.X = 0;
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
		else if (j == 83 && pos.X < vs[pos.Y].length()) //Delete
		{
			vs[pos.Y].erase(pos.X, 1);
		}
		break;
	default:
		if (i >= 32 && i <= 126)
		{
			writeToString(vs[pos.Y], pos, (char)i);
			pos.X += 1;
		}
	}
}

void testCursor()
{
	int i = 0;
	int min = 0;
	int max = 12;
	COORD pos = { 0,0 };
	std::vector<std::string> vs;
	vs.push_back("");
	//std::cout << vs[pos.Y];
	while (i != 27)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		i = _getch();
		handleInput(pos, vs, i);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, pos.Y });
		//std::cout << vs[pos.Y] << " ";
		//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos2);
		//std::cout << i << "    " << '\n';
	}
	//std::wcout << std::endl;
}