#ifndef _TETRIS_TETROMINO_HPP
#define _TETRIS_TETROMINO_HPP

#include<vector>
#include"terminalColors.hpp"

using TerminalBgColor = terminalColors::BackgroundColors;

/*
	Tetromino definition in short:
	The pieces that fall down from the sky
	shaped with letters I, O, T, S, Z, J, and L

	Tetromino definition in detail:
	https://tetris.wiki/Tetromino
*/

namespace tetromino {
	class Tetromino {
	public:
		Tetromino(std::vector<std::vector<terminalColors::BackgroundColors>>&&);
		Tetromino(std::initializer_list<std::initializer_list<terminalColors::BackgroundColors>>&&);

		void rotate(const bool = true) noexcept;

		friend std::ostream& operator<<(std::ostream&, const Tetromino&);
	private:
		std::vector<std::vector<terminalColors::BackgroundColors>> m_shape{};
	};
}

#endif