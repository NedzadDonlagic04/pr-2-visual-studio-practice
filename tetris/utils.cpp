#include"utils.hpp"
#include"terminalColors.hpp"

#include<iostream>
#include<chrono>
#include<thread>

/*
	Source for the various cursor movement ansi codes (and possibly others)
	https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#cursor-controls
*/

namespace utils {
	void moveCursorToPosition(const int x, const int y) {
		if (x < 0 || y < 0) {
			throw std::invalid_argument("Cursor can't be moved to a negative x or y position");
		}

		std::cout << "\033[" << y << ";" << x << "H";
	}

	void printTextWithBgColor(const std::string_view text, TerminalBgColor terminalBgColor) {
		const std::string_view bgColor = terminalColors::backgroundColors.at(terminalBgColor);
		const std::string_view defaultBgColor = terminalColors::backgroundColors.at(terminalColors::BackgroundColors::Default);

		std::cout << bgColor << text << defaultBgColor;
	}

	void clearScreen() noexcept {
		std::cout << "\033[2J\033[H";
	}

	void delayMs(const int64_t miliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
	}
}