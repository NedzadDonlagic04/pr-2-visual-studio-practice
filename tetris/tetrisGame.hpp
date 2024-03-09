#ifndef _TETRIS_TETRIS_GAME_HPP
#define _TETRIS_TETRIS_GAME_HPP

#include<vector>
#include"terminalColors.hpp"

using TerminalBgColor = terminalColors::BackgroundColors;

namespace tetris {
	// -------------------------------------
	// LinesClearedInfo class declaration
	// -------------------------------------
	class LinesClearedInfo {
	public:
		LinesClearedInfo() = default;
		LinesClearedInfo(const std::string_view, const std::size_t = 0);

		[[nodiscard]] std::string_view getLineInfoText() const noexcept;
		[[nodiscard]] int getLinesCleared() const noexcept;

		void incrementLinesCleared() noexcept;
		void printLinesClearedInfo() const noexcept;
	private:
		std::string_view m_lineInfoText{};
		int m_linesCleared{};
		const std::size_t m_windowWidth{};
	};

	// -------------------------------------
	// PlayField class declaration
	// -------------------------------------
	class PlayField {
	public:
		PlayField() = default;
		PlayField(const std::size_t, const std::size_t, const std::string_view = "  ");
		
		[[nodiscard]] std::string_view getPlayFieldBlock() const noexcept;
		[[nodiscard]] std::size_t getPlayFieldWidth() const noexcept;
		[[nodiscard]] std::size_t getPlayFieldHeight() const noexcept;

		void printPlayField(const bool = false) const noexcept;
	private:
		const std::vector<std::vector<TerminalBgColor>> m_playField{};
		const std::string_view m_playFieldBlock {};

		constexpr static std::size_t spawnAreaHeight{ 5 };
		constexpr static TerminalBgColor borberColor{ TerminalBgColor::grey };

		void printPlayFieldBorderLine() const noexcept;
		void printChunkOfPlayField(const std::size_t, const std::size_t) const noexcept;
	};

	// -------------------------------------
	// TetrisGame class declaration
	// -------------------------------------
	class TetrisGame 
		: public PlayField
		, public LinesClearedInfo {
	public:
		TetrisGame();

		void run();
	private:
		void printGameIntroInfo() const noexcept;
		void startMainGameLoop();

		constexpr static std::size_t intendedGameScreenWidth{ 10 };
		constexpr static std::size_t intendedGameScreenHeight { 20 };
	};
}

#endif