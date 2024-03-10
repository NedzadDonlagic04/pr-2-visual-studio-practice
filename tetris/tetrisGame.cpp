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
	LinesClearedInfo::LinesClearedInfo(const std::string_view linesInfoText, const std::size_t playFieldWidth)
		: m_lineInfoText(linesInfoText)
		, m_linesCleared(0)
	{}

	std::string_view LinesClearedInfo::getLineInfoText() const noexcept {
		return m_lineInfoText;
	}

	int LinesClearedInfo::getLinesCleared() const noexcept {
		return m_linesCleared;
	}

	void LinesClearedInfo::incrementLinesCleared() noexcept {
		++m_linesCleared;

		if (m_linesCleared > maxLinesCleared) {
			m_linesCleared = 0;
		}
	}

	// -------------------------------------
	// PlayField class definition
	// -------------------------------------

	// public members below
	PlayField::PlayField()
		: m_playField(std::vector<std::vector<TerminalBgColor>>(totalAreaHeight, std::vector<TerminalBgColor>(totalAreaWidth, TerminalBgColor::Default)))
	{}

	std::size_t PlayField::getPlayFieldWidth() const noexcept {
		return m_playField[0].size();
	}

	std::size_t PlayField::getPlayFieldHeight() const noexcept {
		return m_playField.size();
	}

	void PlayField::printPlayField(const bool showSpawnArea) const noexcept {
		// Used for debugging
		if (showSpawnArea) {
			printChunkOfPlayField(0, spawnAreaHeight);
		}

		printChunkOfPlayField(spawnAreaHeight, getPlayFieldHeight());
		printPlayFieldBorderLine();
	}

	void PlayField::spawnTetrominoOnPlayField(const tetromino::Tetromino& tetromino) {
		const std::size_t initialX{ 0 };
		const std::size_t initialY{ (getPlayFieldWidth() - tetromino.getShapeWidth()) / 2 };
		
		for (std::size_t i = 0; i < tetromino.getShapeHeight(); ++i) {
			for (std::size_t ii = 0; ii < tetromino.getShapeWidth(); ++ii) {
				m_playField[i + initialX][ii + initialY] = tetromino(i, ii);
			}
		}
	}

	// private members below

	void PlayField::printPlayFieldBorderLine() const noexcept {
		// The + 2 in the condition is for it to take into account the sides
		// you can remove it to see it's effects better
		for (std::size_t i = 0; i < m_playField[0].size() + 2; ++i) {
			utils::printTextWithBgColor(playFieldBlock, borberColor);
		}
		std::cout << '\n';
	}

	void PlayField::printChunkOfPlayField(const std::size_t start, const std::size_t end) const noexcept {
		printPlayFieldBorderLine();

		for (std::size_t i = start; i < end; ++i) {
			utils::printTextWithBgColor(playFieldBlock, borberColor);

			for (std::size_t ii = 0; ii < m_playField[i].size(); ++ii) {
				utils::printTextWithBgColor(playFieldBlock, m_playField[i][ii]);
			}

			utils::printTextWithBgColor(playFieldBlock, borberColor);
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
		, m_tetrominos(tetromino::tetrominos)
		, m_rng(std::random_device()())
	{
		// shuffleTetrominos();
	}

	void TetrisGame::run() {
		// printGameIntroInfo();
		startMainGameLoop();
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
		printLinesClearedInfo();

		spawnTetrominoOnPlayField(getCurrentTetromino());

		// put true here to show the spawn area for the
		// tetrominos
		printPlayField(true);

		// utils::delayMs(2000);
		// utils::clearScreen();
	}

	void TetrisGame::printLinesClearedInfo() const noexcept {
		// Save the initial formatting for std::cout
		std::ios initialFormatting{ nullptr };
		initialFormatting.copyfmt(std::cout);

		const auto& maxLinesClearedWidth{ utils::getDigitWidth(maxLinesCleared) };

		const int64_t fullInfoSize = getLineInfoText().size() + separator.size() + maxLinesClearedWidth;

		// The addition of 2 below is so the borders of the play field are taken into account
		// The integer division by 2 is intentional (until it becomes a bug then it isn't)
		const int64_t fullPlayFieldWidth = (getPlayFieldWidth() + 2) * playFieldBlock.size();

		const int64_t paddingSize{ (fullInfoSize >= fullPlayFieldWidth) ? 0 : (fullPlayFieldWidth - fullInfoSize) / 2 };

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

		if (m_tetrominos.size() == 0) {
			m_tetrominos = tetromino::tetrominos;
		}

		shuffleTetrominos();
	}

	tetromino::Tetromino& TetrisGame::getCurrentTetromino() noexcept {
		return m_tetrominos.back();
	}
}