#ifndef TETRIS_TETRIS_GAME_HPP
#define TETRIS_TETRIS_GAME_HPP

#include"terminalColors.hpp"
#include"tetromino.hpp"
#include"utils.hpp"

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

		void printPlayField(const tetromino::Points&, const bool = false) const noexcept;
		void printPlayField(const bool = false) const noexcept;

		[[nodiscard]] bool isPlayFieldDefaultAt(const tetromino::Points::PointType&) const noexcept;
		[[nodiscard]] bool isPointInPlayField(const tetromino::Points::PointType&) const noexcept;

		[[nodiscard]] bool canTetrominoMoveDown(const tetromino::Points&) const noexcept;
		[[nodiscard]] bool canTetrominoMoveLeft(const tetromino::Points&) const noexcept;
		[[nodiscard]] bool canTetrominoMoveRight(const tetromino::Points&) const noexcept;
		[[nodiscard]] bool canTetrominoBeRotated(const tetromino::Points&) const noexcept;

		void rotateTetromino(tetromino::Points&, const bool = false) noexcept;

	protected:
		constexpr static std::size_t spawnAreaHeight{ 5 };
		constexpr static std::size_t playAreaHeight{ 20 };
		constexpr static std::size_t totalAreaHeight{ spawnAreaHeight + playAreaHeight };
		constexpr static std::size_t totalAreaWidth{ 10 };

		constexpr static TerminalBgColor borderColor{ TerminalBgColor::grey };
		constexpr static TerminalBgColor bgColor { TerminalBgColor::Default };

		constexpr static std::string_view playFieldBlock{ "  " };

		void spawnTetrominoOnPlayField(tetromino::Points&) noexcept;

		void moveTetrominoDown(tetromino::Points&);

		void setPlayFieldPoint(const std::size_t, const std::size_t, const TerminalBgColor) noexcept;
		void drawTetromino(const tetromino::Points&) noexcept;

		[[nodiscard]] bool wasSpawnLineCrossed() const noexcept;
	
		std::size_t removeFullRows() noexcept;

	private:
		std::vector<std::vector<TerminalBgColor>> m_playField{};

		void printPlayFieldBorderLine() const noexcept;
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
		std::vector<tetromino::Points> m_tetrominos{ tetromino::tetrominos };
		std::mt19937 m_rng{ std::random_device()() };

		bool m_isCurrentTetrminoLockedIn{ true };
		int64_t m_milisecondsPassed{ 0 };

		const std::unordered_map<char, std::function<void()>> m_keyPressEvents{
			{ 
				'q', [&]() {
					rotateTetromino(getCurrentTetromino());
				}
			},
			{
				'e', [&]() {
					rotateTetromino(getCurrentTetromino(), true);
				}
			},
			{
				'j', [&]() {
					auto& currentTetromino{ getCurrentTetromino() };

					if (!canTetrominoMoveLeft(currentTetromino)) {
						return;
					}

					for (auto& point : currentTetromino) {
						--point.second;
					}
					currentTetromino.moveOffsetLeft();
				}
			},
			{
				'l', [&]() {
					auto& currentTetromino{ getCurrentTetromino() };

					if (!canTetrominoMoveRight(currentTetromino)) {
						return;
					}

					for (auto& point : currentTetromino) {
						++point.second;
					}
					currentTetromino.moveOffsetRight();
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

		[[nodiscard]] tetromino::Points& getCurrentTetromino() noexcept;
		
		[[nodiscard]] int64_t getCurrentMsPassed() const noexcept;
		void incrementMsPassed() noexcept;
		
		void setIsCurrentTetrominoLockedIn(const bool) noexcept;
		void setMsPassed(const int64_t) noexcept;
	};
}

#endif	// TETRIS_TETRIS_GAME_HPP