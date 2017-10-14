#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <iostream>

class InputHandler
{
private:
	static void repositionPos(std::vector<std::string> &vs, COORD &pos);
	static void handleInput(COORD &pos, std::vector<std::string> &vs, int i, bool &run_calculator_loop, bool &run_input_loop, bool &string_untouched);
public:
	static void clearLine(int line);
	static inline void setCursorPosition(int x, int y);
	static int getInput(std::vector<std::string> &strings, bool &run_calculator_loop);
};