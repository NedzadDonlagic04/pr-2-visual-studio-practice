#include"utils.hpp"
#include"terminalColors.hpp"

#include<iostream>
#include<chrono>
#include<thread>
#include<cmath>
#include<limits>

// For key pressed shenanigans
#include<conio.h>
#include<windows.h>

/*
	Source for the various cursor movement ansi codes (and possibly others)
	https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#cursor-controls
*/

namespace utils {
	void setCursorPosition(const int x, const int y) {
		if (x < 0 || y < 0) {
			throw std::invalid_argument("Cursor can't be moved to a negative x or y position");
		}

		std::cout << "\033[" << y << ";" << x << "H";
	}

	void printTextWithBgColor(const std::string_view text, TerminalBgColor terminalBgColor) noexcept {
		const std::string_view bgColor = terminalColors::backgroundColors.at(terminalBgColor);
		const std::string_view defaultBgColor = terminalColors::backgroundColors.at(terminalColors::BackgroundColors::Default);

		std::cout << bgColor << text << defaultBgColor;
	}

	std::streamsize getDigitWidth(const int num) noexcept {
		const bool isNeg{ num < 0 };

		// static cast to std::streamsize because the result of std::log10 
		// is double
		return static_cast<std::streamsize>(std::log10(std::abs(num))) + 1 + isNeg;
	}

	void clearScreen() noexcept {
		setCursorPosition(0, 0);
	}

	void delayMs(const uint64_t miliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
	}

	bool isKeyPressed() noexcept {
		return _kbhit();
	}

	char getPressedKey() noexcept {
		return _getch();
	}
}