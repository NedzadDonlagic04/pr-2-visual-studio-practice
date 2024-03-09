#include"tetrisGame.hpp"
#include"utils.hpp"
#include<iostream>
#include<iomanip>
#include"terminalColors.hpp"

using TerminalBgColor = terminalColors::BackgroundColors;

namespace tetris {
	// -------------------------------------
	// LinesClearedInfo class definition
	// -------------------------------------
	
	// public members below
	LinesClearedInfo::LinesClearedInfo(const std::string_view linesInfoText, const std::size_t m_windowWidth)
		: m_lineInfoText(linesInfoText)
		, m_linesCleared(0)
		, m_windowWidth(m_windowWidth)
	{}

	std::string_view LinesClearedInfo::getLineInfoText() const noexcept {
		return m_lineInfoText;
	}

	int LinesClearedInfo::getLinesCleared() const noexcept {
		return m_linesCleared;
	}

	void LinesClearedInfo::incrementLinesCleared() noexcept {
		++m_linesCleared;

		if (m_linesCleared > 999) {
			m_linesCleared = 0;
		}
	}

	void LinesClearedInfo::printLinesClearedInfo() const noexcept {
		// Save the initial formatting for std::cout
		std::ios initialFormatting{ nullptr };
		initialFormatting.copyfmt(std::cout);

		std::cout << m_lineInfoText << " - ";
		std::cout << std::setw(3) << std::setfill('0') << m_linesCleared << '\n';

		// Restore initial std::cout formatting
		std::cout.copyfmt(initialFormatting);
	}

	// -------------------------------------
	// PlayField class definition
	// -------------------------------------
	
	// public members below
	PlayField::PlayField(const std::size_t rowSize, const std::size_t colSize, const std::string_view playFieldBlock)
		: m_playField(std::vector<std::vector<TerminalBgColor>>(rowSize + spawnAreaHeight, std::vector<TerminalBgColor>(colSize, TerminalBgColor::Default)))
		, m_playFieldBlock(playFieldBlock)
	{}

	std::string_view PlayField::getPlayFieldBlock() const noexcept {
		return m_playFieldBlock;
	}

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

	// private members below

	void PlayField::printPlayFieldBorderLine() const noexcept {
		// The + 2 in the condition is for it to take into account the sides
		// you can remove it to see it's effects better
		for (std::size_t i = 0; i < m_playField[0].size() + 2; i++) {
			utils::printTextWithBgColor(getPlayFieldBlock(), borberColor);
		}
		std::cout << '\n';
	}

	void PlayField::printChunkOfPlayField(const std::size_t start, const std::size_t end) const noexcept {
		printPlayFieldBorderLine();

		for (std::size_t i = start; i < end; i++) {
			utils::printTextWithBgColor(getPlayFieldBlock(), borberColor);

			for (std::size_t ii = 0; ii < m_playField[i].size(); ii++) {
				utils::printTextWithBgColor(getPlayFieldBlock(), m_playField[i][ii]);
			}

			utils::printTextWithBgColor(getPlayFieldBlock(), borberColor);
			std::cout << '\n';
		}
	}

	// -------------------------------------
	// TetrisGame class definition
	// -------------------------------------
	
	// public members below
	TetrisGame::TetrisGame() 
		: PlayField(intendedGameScreenHeight, intendedGameScreenWidth)
		, LinesClearedInfo("Lines cleared", intendedGameScreenWidth)
	{}

	void TetrisGame::run() {
		printGameIntroInfo();
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

		// put true here to show the spawn area for the
		// tetrominos
		printPlayField(true);

		// utils::delayMs(2000);
		// utils::clearScreen();
	}
}