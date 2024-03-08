#include"utils.hpp"
#include"terminalColors.hpp"

#include<iostream>

namespace utils {
	void moveCursorToPosition(const int x, const int y) {
		if (x < 0 || y < 0) {
			throw std::invalid_argument("Cursor can't be moved to a negative x or y position");
		}

		std::cout << "\033[" << y << ";" << x << "H";
	}

	void colorSpaceInTerminal(TerminalBgColor terminalBgColor) {
		const std::string_view bgColor = terminalColors::backgroundColors.at(terminalBgColor);
		const std::string_view defaultBgColor = terminalColors::backgroundColors.at(terminalColors::BackgroundColors::Default);

		std::cout << bgColor << "  "  << defaultBgColor;
	}
}