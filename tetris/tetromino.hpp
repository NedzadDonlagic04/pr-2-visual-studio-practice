#ifndef _TETRIS_TETROMINO_HPP
#define _TETRIS_TETROMINO_HPP

#include<vector>
#include<array>
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
	// -------------------------------------
	// Tetromino class declaration
	// -------------------------------------
	class Tetromino {
	public:
		Tetromino(const std::vector<std::vector<terminalColors::BackgroundColors>>&);
		Tetromino(std::vector<std::vector<terminalColors::BackgroundColors>>&&);
		Tetromino(std::initializer_list<std::initializer_list<terminalColors::BackgroundColors>>&&);

		[[nodiscard]] std::size_t getShapeHeight() const noexcept;
		[[nodiscard]] std::size_t getShapeWidth() const noexcept;

		void rotate(const bool = true) noexcept;

		friend std::ostream& operator<<(std::ostream&, const Tetromino&);
	private:
		std::vector<std::vector<terminalColors::BackgroundColors>> m_shape{};
	};

	// -------------------------------------
	// functions and constants declaration / definitions
	// -------------------------------------

	void printAllRotationsOfATetromino(Tetromino&);

	/*
		Rotation and shapes with sizes were all decided after reading the page below
		https://tetris.wiki/Super_Rotation_System
	*/
	constexpr std::size_t maxTetrominos{ 7 };
	inline const std::array<Tetromino, maxTetrominos> tetrominos{
		// I shape
		Tetromino{
			{TerminalBgColor::grey,      TerminalBgColor::grey,      TerminalBgColor::grey,      TerminalBgColor::grey},
			{TerminalBgColor::lightBlue, TerminalBgColor::lightBlue, TerminalBgColor::lightBlue, TerminalBgColor::lightBlue},
			{TerminalBgColor::grey,      TerminalBgColor::grey,      TerminalBgColor::grey,      TerminalBgColor::grey},
			{TerminalBgColor::grey,      TerminalBgColor::grey,      TerminalBgColor::grey,      TerminalBgColor::grey},
		},
		// J shape
		Tetromino{
			{TerminalBgColor::darkBlue, TerminalBgColor::grey,     TerminalBgColor::grey},
			{TerminalBgColor::darkBlue, TerminalBgColor::darkBlue, TerminalBgColor::darkBlue},
			{TerminalBgColor::grey,     TerminalBgColor::grey,     TerminalBgColor::grey},
		},
		// L shape
		Tetromino{
			{TerminalBgColor::grey,   TerminalBgColor::grey,   TerminalBgColor::orange},
			{TerminalBgColor::orange, TerminalBgColor::orange, TerminalBgColor::orange},
			{TerminalBgColor::grey,   TerminalBgColor::grey,   TerminalBgColor::grey},
		},
		// O shape
		Tetromino{
			{TerminalBgColor::yellow, TerminalBgColor::yellow},
			{TerminalBgColor::yellow, TerminalBgColor::yellow},
		},
		// S shape
		Tetromino{
			{TerminalBgColor::grey,  TerminalBgColor::green,  TerminalBgColor::green},
			{TerminalBgColor::green, TerminalBgColor::green, TerminalBgColor::grey},
			{TerminalBgColor::grey,  TerminalBgColor::grey,   TerminalBgColor::grey},
		},
		// T shape
		Tetromino{
			{TerminalBgColor::grey,    TerminalBgColor::magenta, TerminalBgColor::grey},
			{TerminalBgColor::magenta, TerminalBgColor::magenta, TerminalBgColor::magenta},
			{TerminalBgColor::grey,    TerminalBgColor::grey,    TerminalBgColor::grey},
		},
		// Z shape
		Tetromino{
			{TerminalBgColor::red,  TerminalBgColor::red,  TerminalBgColor::grey},
			{TerminalBgColor::grey, TerminalBgColor::red,  TerminalBgColor::red},
			{TerminalBgColor::grey, TerminalBgColor::grey, TerminalBgColor::grey},
		}
	};
}

#endif