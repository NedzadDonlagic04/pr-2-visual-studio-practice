#ifndef _TETRIS_UTILS_HEADER
#define _TETRIS_UTILS_HEADER

/*
	A lot of the ANSI related stuff I found was from the link below
	https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

	Do note using ANSI isn't a good solution, generally a library
	is better due to portability
*/

namespace utils {
	void moveCursorToPosition(const int, const int);
}

#endif