#include"tetrisGame.hpp"
#include"utils.hpp"
#include"terminalColors.hpp"
#include"tetromino.hpp"

#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>
#include<random>

using TerminalBgColor = terminalColors::BackgroundColors;

namespace tetris {
	// -------------------------------------
	// LinesClearedInfo class definition
	// -------------------------------------

	// public members below
	LinesClearedInfo::LinesClearedInfo(const std::string_view linesInfoText)
		: m_lineInfoText(linesInfoText)
	{}

	std::string_view LinesClearedInfo::getLineInfoText() const noexcept {
		return m_lineInfoText;
	}

	int LinesClearedInfo::getLinesCleared() const noexcept {
		return m_linesCleared;
	}

	// protected members below
	void LinesClearedInfo::setLinesCleared(const int linesCleared) noexcept {
		m_linesCleared = linesCleared;
	}

	void LinesClearedInfo::incrementLinesCleared() noexcept {
		++m_linesCleared;

		if (m_linesCleared > maxLinesCleared) {
			setLinesCleared(0);
		}
	}

	// -------------------------------------
	// PlayField class definition
	// -------------------------------------

	// public members below
	PlayField::PlayField()
		: m_playField(std::vector<std::vector<TerminalBgColor>>(
			totalAreaHeight,
			std::vector<TerminalBgColor>(totalAreaWidth, TerminalBgColor::Default))
		)
	{}

	std::size_t PlayField::getPlayFieldWidth() const noexcept {
		return m_playField[0].size();
	}

	std::size_t PlayField::getPlayFieldHeight() const noexcept {
		return m_playField.size();
	}

	std::size_t PlayField::getCurrentTetrominoX() const noexcept {
		return m_currentTetrominoX;
	}

	std::size_t PlayField::getCurrentTetrominoY() const noexcept {
		return m_currentTetrominoY;
	}

	void PlayField::printPlayField(const tetromino::Tetromino &tetromino, const bool showSpawnArea) const noexcept {
		TerminalBgColor bgColorToDraw{};

		const auto areIndexesInRangeOfTetromino = [&](const std::size_t i, const std::size_t ii) {
			const auto initialX{ getCurrentTetrominoX() };
			const auto initialY{ getCurrentTetrominoY() };

			return i >= initialX
				&& i < initialX + tetromino.getShapeHeight()
				&& ii >= initialY
				&& ii < initialY + tetromino.getShapeWidth();
		};

		const auto isCurrentTetrominoSpotDefaultColored = [&](const std::size_t i, const std::size_t ii) {
			return tetromino(i - getCurrentTetrominoX(), ii - getCurrentTetrominoY()) == TerminalBgColor::Default;
		};

		printPlayFieldBorderLine();

		for (std::size_t i = (showSpawnArea)? 0 : spawnAreaHeight; i < getPlayFieldHeight(); ++i) {
			if (showSpawnArea && i == spawnAreaHeight) {
				printPlayFieldBorderLine();
			}

			utils::printTextWithBgColor(playFieldBlock, borderColor);
			
			for (std::size_t ii = 0; ii < m_playField[i].size(); ++ii) {
				bgColorToDraw = (areIndexesInRangeOfTetromino(i, ii) && !isCurrentTetrominoSpotDefaultColored(i, ii)) ?
					tetromino(i - getCurrentTetrominoX(), ii - getCurrentTetrominoY())
					: m_playField[i][ii];
				
				utils::printTextWithBgColor(playFieldBlock, bgColorToDraw);
			}

			utils::printTextWithBgColor(playFieldBlock, borderColor);
			std::cout << '\n';
		}

		printPlayFieldBorderLine();
	}

	bool PlayField::checkCanTetrominoMoveDown(const tetromino::Tetromino& tetromino) noexcept {
		if (getCurrentTetrominoX() + tetromino.getShapeHeight() >= getPlayFieldHeight()) {
			return false;
		}

		for (std::size_t i = 0; i < tetromino.getShapeHeight(); ++i) {
			for (std::size_t ii = 0; ii < tetromino.getShapeWidth(); ++ii) {
				const bool isCurrentPlayFieldBlockDefault{ m_playField[i + 1 + getCurrentTetrominoX()][ii + getCurrentTetrominoY()] != TerminalBgColor::Default};
				const bool isCurrentTetrominoBlockDefault{ tetromino(i, ii) != TerminalBgColor::Default };

				if (isCurrentPlayFieldBlockDefault && isCurrentTetrominoBlockDefault) {
					return false;
				}
			}
		}

		return true;
	}

	// protected members below

	void PlayField::spawnTetrominoOnPlayField(const tetromino::Tetromino& tetromino) noexcept {
		setCurrentTetrominoPosition(tetromino);
	}

	void PlayField::moveTetrominoDown(const tetromino::Tetromino& tetromino) {
		const auto isTetrominoOutOfPlayFieldRange = [&]() {
			return getCurrentTetrominoX() + tetromino.getShapeHeight() >= getPlayFieldHeight();
		};

		if (isTetrominoOutOfPlayFieldRange()) {
			throw std::out_of_range("Tetromino drawn out of bounds of playfield");
		}
		
		moveDownALine();
	}

	void PlayField::drawTetromino(const tetromino::Tetromino& tetromino) noexcept {
		for (std::size_t i = 0; i < tetromino.getShapeHeight(); ++i) {
			for (std::size_t ii = 0; ii < tetromino.getShapeWidth(); ++ii) {
				if (tetromino(i, ii) != TerminalBgColor::Default) {
					m_playField[i + getCurrentTetrominoX()][ii + getCurrentTetrominoY()] = tetromino(i, ii);
				}
			}
		}
	}

	bool PlayField::wasSpawnLineCrossed() const noexcept {
		return !std::all_of(m_playField[spawnAreaHeight - 1].begin(), m_playField[spawnAreaHeight - 1].end(),
			[](const auto color) {
				return color == TerminalBgColor::Default;
			}
		);
	}

	// private members below

	void PlayField::setCurrentTetrominoX(const std::size_t currentTetrominoX) noexcept {
		m_currentTetrominoX = currentTetrominoX;
	}

	void PlayField::setCurrentTetrominoY(const std::size_t currentTetrominoY) noexcept {
		m_currentTetrominoY = currentTetrominoY;
	}

	void PlayField::setCurrentTetrominoPosition(const tetromino::Tetromino &tetromino) noexcept {
		setCurrentTetrominoX(0);
		setCurrentTetrominoY((getPlayFieldWidth() - tetromino.getShapeWidth()) / 2);
	}

	void PlayField::moveDownALine() noexcept {
		m_currentTetrominoX++;
	}

	void PlayField::printPlayFieldBorderLine() const noexcept {
		// The + 2 in the condition is for it to take into account the sides
		// you can remove it to see it's effects better
		for (std::size_t i = 0; i < m_playField[0].size() + 2; ++i) {
			utils::printTextWithBgColor(playFieldBlock, borderColor);
		}
		std::cout << '\n';
	}

	void PlayField::printChunkOfPlayField(const std::size_t start, const std::size_t end) const noexcept {
		printPlayFieldBorderLine();

		for (std::size_t i = start; i < end; ++i) {
			utils::printTextWithBgColor(playFieldBlock, borderColor);

			for (std::size_t ii = 0; ii < m_playField[i].size(); ++ii) {
				utils::printTextWithBgColor(playFieldBlock, m_playField[i][ii]);
			}

			utils::printTextWithBgColor(playFieldBlock, borderColor);
			std::cout << '\n';
		}
	}

	// -------------------------------------
	// TetrisGame class definition
	// -------------------------------------

	// public members below
	TetrisGame::TetrisGame()
		: LinesClearedInfo("Lines cleared")
		, PlayField()
	{
		shuffleTetrominos();
	}

	void TetrisGame::run() {
		// printGameIntroInfo();
		startMainGameLoop();
	}

	bool TetrisGame::isGameOver() const noexcept {
		return wasSpawnLineCrossed();
	}

	// private members below
	void TetrisGame::printGameIntroInfo() const noexcept {
		std::cout << "Hello and welcome to my attempt at recreating Tetris in the terminal\n";
		std::cout << "Preferably resize the terminal to take up the full screen so nothing goes out of bounds\n\n";
		std::cout << "The controls are:\n";
		std::cout << "Arrow keys used for moving pieces left or right\n";
		std::cout << "Q and E are used to rotate the pieces 90 deg left or right\n";
		std::cout << "W is used to move the piece row by row down, this will also happen naturally but more slowly\n";
		std::cout << "Space will move it down instantly down to the silhouette shown in white\n\n";
		std::cout << "When you've read and understood all of this press any key to start the game...";
		std::cin.get();

		utils::clearScreen();
	}

	void TetrisGame::startMainGameLoop() {
		while (1) {
			utils::clearScreen();

			auto&currentTetromino{ getCurrentTetromino() };

			if (m_isCurrentTetrminoLockedIn) {
				spawnTetrominoOnPlayField(currentTetromino);
				setIsCurrentTetrominoLockedIn(false);
			}

			printLinesClearedInfo();
			// put true here to show the spawn area for the
			// tetrominos
			printPlayField(currentTetromino, true);

			utils::delayMs(msPassedEachLoop);
			incrementMsPassed();

			const bool didEnoughTimePassForMove{ getCurrentMsPassed() >= msNeededFor1MoveDown };
			const bool canTetrominoMoveDown{ checkCanTetrominoMoveDown(currentTetromino) };

			if (didEnoughTimePassForMove && !canTetrominoMoveDown) {
				setIsCurrentTetrominoLockedIn(true);
				setMsPassed(0);
				drawTetromino(currentTetromino);
				removeLastUsedTetromino();

				if (isGameOver()) {
					break;
				}
			}
			else if (didEnoughTimePassForMove && canTetrominoMoveDown) {
				moveTetrominoDown(currentTetromino);
				setMsPassed(0);
			}
		}

		std::cout << "Game over man\n";
	}

	void TetrisGame::printLinesClearedInfo() const noexcept {
		// Save the initial formatting for std::cout
		std::ios initialFormatting{ nullptr };
		initialFormatting.copyfmt(std::cout);

		const auto& maxLinesClearedWidth{ utils::getDigitWidth(maxLinesCleared) };

		// IIFE
		const int64_t paddingSize{ [&]() {
			const int64_t fullInfoSize = getLineInfoText().size() + separator.size() + maxLinesClearedWidth;

			// The addition of 2 below is so the borders of the play field are taken into account
			// The integer division by 2 is intentional (until it becomes a bug then it isn't)
			const int64_t fullPlayFieldWidth = (getPlayFieldWidth() + 2) * playFieldBlock.size();

			return (fullInfoSize >= fullPlayFieldWidth) ? 0 : (fullPlayFieldWidth - fullInfoSize) / 2;
		}() };

		std::cout << std::string(paddingSize, ' ') << getLineInfoText() << separator;
		std::cout << std::setw(maxLinesClearedWidth) << std::setfill('0') << getLinesCleared() << '\n';

		// Restore initial std::cout formatting
		std::cout.copyfmt(initialFormatting);
	}

	void TetrisGame::shuffleTetrominos() noexcept {
		std::shuffle(m_tetrominos.begin(), m_tetrominos.end(), m_rng);
	}

	void TetrisGame::removeLastUsedTetromino() noexcept {
		m_tetrominos.pop_back();

		if (!m_tetrominos.size()) {
			m_tetrominos = tetromino::tetrominos;
		}

		shuffleTetrominos();
	}

	tetromino::Tetromino& TetrisGame::getCurrentTetromino() noexcept {
		return m_tetrominos.back();
	}

	int64_t TetrisGame::getCurrentMsPassed() const noexcept {
		return m_milisecondsPassed;
	}

	void TetrisGame::incrementMsPassed() noexcept {
		m_milisecondsPassed += msPassedEachLoop;
	}

	void TetrisGame::setIsCurrentTetrominoLockedIn(const bool isCurrentTetrominoLockedIn) noexcept {
		m_isCurrentTetrminoLockedIn = isCurrentTetrominoLockedIn;
	}

	void TetrisGame::setMsPassed(const int64_t milisecondsPassed) noexcept {
		m_milisecondsPassed = milisecondsPassed;
	}
}