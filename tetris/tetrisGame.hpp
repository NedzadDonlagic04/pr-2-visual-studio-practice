#ifndef _TETRIS_TETRIS_GAME_HPP
#define _TETRIS_TETRIS_GAME_HPP

#include"terminalColors.hpp"
#include"tetromino.hpp"

#include<vector>
#include<random>
#include<utility>

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

		virtual void printLinesClearedInfo() const noexcept = 0;
	
	protected:
		constexpr static int maxLinesCleared{ 999 };
		constexpr static std::string_view separator{ " - " };

		void incrementLinesCleared() noexcept;

	private:
		std::string_view m_lineInfoText{};
		int m_linesCleared{};
	};

	// -------------------------------------
	// PlayField class declaration
	// -------------------------------------
	class PlayField {
	public:
		PlayField();
		
		[[nodiscard]] std::size_t getPlayFieldWidth() const noexcept;
		[[nodiscard]] std::size_t getPlayFieldHeight() const noexcept;

		void printPlayField(const bool = false) const noexcept;

	protected:
		constexpr static std::size_t spawnAreaHeight{ 5 };
		constexpr static std::size_t playAreaHeight{ 20 };
		constexpr static std::size_t totalAreaHeight{ spawnAreaHeight + playAreaHeight };
		constexpr static std::size_t totalAreaWidth{ 10 };

		constexpr static TerminalBgColor borberColor{ TerminalBgColor::grey };
		constexpr static std::string_view playFieldBlock{ "  " };
	
		void spawnTetrominoOnPlayField(const tetromino::Tetromino&);

	private:
		std::vector<std::vector<TerminalBgColor>> m_playField{};

		void printPlayFieldBorderLine() const noexcept;
		void printChunkOfPlayField(const std::size_t, const std::size_t) const noexcept;
	};

	// -------------------------------------
	// TetrisGame class declaration
	// -------------------------------------
	class TetrisGame 
		: public LinesClearedInfo
		, public PlayField {
	public:
		TetrisGame();

		void run();
	
	private:
		std::vector<tetromino::Tetromino> m_tetrominos{};
		std::mt19937 m_rng{};

		void printGameIntroInfo() const noexcept;
		void startMainGameLoop();

		void printLinesClearedInfo() const noexcept override;

		void shuffleTetrominos() noexcept;
		void removeLastUsedTetromino() noexcept;

		[[nodiscard]] tetromino::Tetromino& getCurrentTetromino() noexcept;
	};
}

#endif