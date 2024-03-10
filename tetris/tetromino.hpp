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
	private:
		std::vector<std::vector<terminalColors::BackgroundColors>> m_shape{};
	};

	// -------------------------------------
	// functions and constants declaration / definitions
	// -------------------------------------

	/*
		Rotation and shapes with sizes were all decided after reading the page below
		https://tetris.wiki/Super_Rotation_System
	*/
	inline const std::vector<Tetromino> tetrominos{
		// I shape
		Tetromino{
			{TerminalBgColor::Default  , TerminalBgColor::Default  , TerminalBgColor::Default  , TerminalBgColor::Default},
			{TerminalBgColor::lightBlue, TerminalBgColor::lightBlue, TerminalBgColor::lightBlue, TerminalBgColor::lightBlue},
			{TerminalBgColor::Default  , TerminalBgColor::Default  , TerminalBgColor::Default  , TerminalBgColor::Default},
			{TerminalBgColor::Default  , TerminalBgColor::Default  , TerminalBgColor::Default  , TerminalBgColor::Default},
		},
		// J shape
		Tetromino{
			{TerminalBgColor::darkBlue, TerminalBgColor::Default , TerminalBgColor::Default},
			{TerminalBgColor::darkBlue, TerminalBgColor::darkBlue, TerminalBgColor::darkBlue},
			{TerminalBgColor::Default , TerminalBgColor::Default , TerminalBgColor::Default},
		},
		// L shape
		Tetromino{
			{TerminalBgColor::Default, TerminalBgColor::Default, TerminalBgColor::orange},
			{TerminalBgColor::orange , TerminalBgColor::orange , TerminalBgColor::orange},
			{TerminalBgColor::Default, TerminalBgColor::Default, TerminalBgColor::Default},
		},
		// O shape
		Tetromino{
			{TerminalBgColor::yellow, TerminalBgColor::yellow},
			{TerminalBgColor::yellow, TerminalBgColor::yellow},
		},
		// S shape
		Tetromino{
			{TerminalBgColor::Default, TerminalBgColor::green  , TerminalBgColor::green},
			{TerminalBgColor::green  , TerminalBgColor::green  , TerminalBgColor::Default},
			{TerminalBgColor::Default, TerminalBgColor::Default, TerminalBgColor::Default},
		},
		// T shape
		Tetromino{
			{TerminalBgColor::Default, TerminalBgColor::magenta, TerminalBgColor::Default},
			{TerminalBgColor::magenta, TerminalBgColor::magenta, TerminalBgColor::magenta},
			{TerminalBgColor::Default, TerminalBgColor::Default, TerminalBgColor::Default},
		},
		// Z shape
		Tetromino{
			{TerminalBgColor::red    , TerminalBgColor::red    , TerminalBgColor::Default},
			{TerminalBgColor::Default, TerminalBgColor::red    , TerminalBgColor::red},
			{TerminalBgColor::Default, TerminalBgColor::Default, TerminalBgColor::Default},
		}
	};
}

#endif