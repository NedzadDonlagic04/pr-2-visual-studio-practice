#ifndef _TETRIS_TETRIS_GAME_HPP
#define _TETRIS_TETRIS_GAME_HPP

#include"terminalColors.hpp"
#include"tetromino.hpp"

#include<vector>
#include<random>
#include<functional>

using TerminalBgColor = terminalColors::BackgroundColors;

namespace tetris {
	// -------------------------------------
	// LinesClearedInfo class declaration
	// -------------------------------------
	class LinesClearedInfo {
	public:

		LinesClearedInfo() = default;
		LinesClearedInfo(const std::string_view);

		[[nodiscard]] std::string_view getLineInfoText() const noexcept;
		[[nodiscard]] int getLinesCleared() const noexcept;

		virtual void printLinesClearedInfo() const noexcept = 0;
	
	protected:
		constexpr static int maxLinesCleared{ 999 };
		constexpr static std::string_view separator{ " - " };

		void setLinesCleared(const int) noexcept;
		void incrementLinesCleared() noexcept;

	private:
		const std::string_view m_lineInfoText{};
		int m_linesCleared{ 0 };
	};

	// -------------------------------------
	// PlayField class declaration
	// -------------------------------------
	class PlayField {
	public:
		PlayField();
		
		[[nodiscard]] std::size_t getPlayFieldWidth() const noexcept;
		[[nodiscard]] std::size_t getPlayFieldHeight() const noexcept;

		[[nodiscard]] std::size_t getCurrentTetrominoX() const noexcept;
		[[nodiscard]] std::size_t getCurrentTetrominoY() const noexcept;

		void printPlayField(const tetromino::Tetromino&, const bool = false) const noexcept;

		[[nodiscard]] bool checkCanTetrominoMoveDown(const tetromino::Tetromino&) noexcept;
	
	protected:
		constexpr static std::size_t spawnAreaHeight{ 5 };
		constexpr static std::size_t playAreaHeight{ 20 };
		constexpr static std::size_t totalAreaHeight{ spawnAreaHeight + playAreaHeight };
		constexpr static std::size_t totalAreaWidth{ 10 };

		constexpr static TerminalBgColor borderColor{ TerminalBgColor::grey };
		constexpr static std::string_view playFieldBlock{ "  " };
	
		void spawnTetrominoOnPlayField(const tetromino::Tetromino&) noexcept;

		void moveTetrominoDown(const tetromino::Tetromino&);
		void drawTetromino(const tetromino::Tetromino&) noexcept;

		[[nodiscard]] bool wasSpawnLineCrossed() const noexcept;
	
	private:
		std::vector<std::vector<TerminalBgColor>> m_playField{};

		std::size_t m_currentTetrominoX{};
		std::size_t m_currentTetrominoY{};

		void setCurrentTetrominoX(const std::size_t) noexcept;
		void setCurrentTetrominoY(const std::size_t) noexcept;
		void setCurrentTetrominoPosition(const tetromino::Tetromino& tetromino) noexcept;

		void moveDownALine() noexcept;

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
	
		[[nodiscard]] bool isGameOver() const noexcept;
	private:
		std::vector<tetromino::Tetromino> m_tetrominos{ tetromino::tetrominos };
		std::mt19937 m_rng{ std::random_device()() };

		bool m_isCurrentTetrminoLockedIn{ true };
		int64_t m_milisecondsPassed{ 0 };

		const std::unordered_map<char, std::function<void()>> m_keyPressEvents{
			{ 
				'q', [&]() {
					getCurrentTetromino().rotateLeft();
				} 
			},
			{
				'e', [&]() {
					getCurrentTetromino().rotateRight();
				}
			},
		};

		constexpr static int64_t msPassedEachLoop{ 100 };
		constexpr static int64_t msNeededFor1MoveDown{ msPassedEachLoop };

		void printGameIntroInfo() const noexcept;
		void startMainGameLoop();

		void printLinesClearedInfo() const noexcept override;

		void shuffleTetrominos() noexcept;
		void removeLastUsedTetromino() noexcept;

		void handleKeyPressActions() noexcept;

		[[nodiscard]] tetromino::Tetromino& getCurrentTetromino() noexcept;
		
		[[nodiscard]] int64_t getCurrentMsPassed() const noexcept;
		void incrementMsPassed() noexcept;
		
		void setIsCurrentTetrominoLockedIn(const bool) noexcept;
		void setMsPassed(const int64_t) noexcept;
	};
}

#endif