#include"utils.hpp"

#include<iostream>

namespace utils {
	void moveCursorToPosition(const int x, const int y) {
		if (x < 0 || y < 0) {
			throw std::invalid_argument("Cursor can't be moved to a negative x or y position");
		}

		std::cout << "\033[" << y << ";" << x << "H";
	}
}