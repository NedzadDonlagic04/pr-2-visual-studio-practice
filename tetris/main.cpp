#include<iostream>
#include<vector>
#include"terminalColors.hpp"
#include"utils.hpp"
#include"tetromino.hpp"

using TerminalBgColor = terminalColors::BackgroundColors;

int main() {
	tetromino::Tetromino tetromino{
		std::vector<std::vector<TerminalBgColor>> {
			{TerminalBgColor::grey, TerminalBgColor::green, TerminalBgColor::green},
			{TerminalBgColor::green, TerminalBgColor::green, TerminalBgColor::grey},
			{TerminalBgColor::grey, TerminalBgColor::grey, TerminalBgColor::grey},
		}
	};

	std::cout << tetromino << '\n';
	tetromino.rotate();

	std::cout << tetromino << '\n';
	tetromino.rotate();

	std::cout << tetromino << '\n';
	tetromino.rotate();

	std::cout << tetromino << '\n';
	tetromino.rotate();

	std::cout << tetromino << '\n';
	
	return 0;
}