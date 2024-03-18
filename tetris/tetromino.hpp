#ifndef _TETRIS_TETROMINO_HPP
#define _TETRIS_TETROMINO_HPP

#include"terminalColors.hpp"

#include<vector>
#include<unordered_set>
#include<utility>

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
	// Points class declaration
	// -------------------------------------
	class Points {
	public:
		using FirstSecondType = std::int64_t;
		using PointType = std::pair<FirstSecondType, FirstSecondType>;

		Points(std::vector<std::vector<char>>&&, TerminalBgColor&&);
		Points(const Points&);
		Points(Points&&) noexcept;

		Points& operator=(const Points&) noexcept;
		Points& operator=(Points&&) noexcept;

		[[nodiscard]] TerminalBgColor getPointsColor() const noexcept;

		using ConstIterator = std::vector<PointType>::const_iterator;
		using Iterator = std::vector<PointType>::iterator;

		ConstIterator begin() const noexcept;
		ConstIterator end() const noexcept;

		Iterator begin() noexcept;
		Iterator end() noexcept;

		void offsetAllPointsBy(const PointType&) noexcept;

		[[nodiscard]] bool doesPointExist(const PointType&) const noexcept;

		void rotateLeft() noexcept;
		void rotateRight() noexcept;

		void moveOffsetUp() noexcept;
		void moveOffsetDown() noexcept;
		void moveOffsetLeft() noexcept;
		void moveOffsetRight() noexcept;

	private:
		std::vector<std::vector<char>> m_pointsMatrix{};
		std::vector<PointType> m_points{};
		PointType m_offsetPoint { 0, 0 };
		TerminalBgColor m_pointsColor{ TerminalBgColor::Default };

		int m_currentRotation{ 0 };

		constexpr static int minRotations{ 0 };
		constexpr static int maxRotations{ 3 };

		void rotate() noexcept;
		void rotate0Deg() noexcept;
		void rotate90Deg() noexcept;
		void rotate180Deg() noexcept;
		void rotate270Deg() noexcept;
	};

	// -------------------------------------
	// constants definition
	// -------------------------------------

	inline const std::vector<Points> tetrominos{
		// I shape
		{ 
			{
				{ 1, 1, 1, 1 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
			}, 
			TerminalBgColor::lightBlue, 
		},
		// J shape
		{
			{
				{ 1, 0, 0 },
				{ 1, 1, 1 },
				{ 0, 0, 0 },
			},
			TerminalBgColor::darkBlue,
		},
		// L shape
		{
			{
				{ 0, 0, 1 },
				{ 1, 1, 1 },
				{ 0, 0, 0 },
			},
			TerminalBgColor::orange,
		},
		// O shape
		{
			{
				{ 1, 1 },
				{ 1, 1 },
			},
			TerminalBgColor::yellow,
		},
		// S shape
		{
			{
				{ 0, 1, 1 },
				{ 1, 1, 0 },
				{ 0, 0, 0 },
			},
			TerminalBgColor::green,
		},
		// T shape
		{
			{
				{ 0, 1, 0 },
				{ 1, 1, 1 },
				{ 0, 0, 0 },
			},
			TerminalBgColor::magenta,
		},
		// Z shape
		{
			{
				{ 1, 1, 0 },
				{ 0, 1, 1 },
				{ 0, 0, 0 },
			},
			TerminalBgColor::red,
		},
	};
}

#endif