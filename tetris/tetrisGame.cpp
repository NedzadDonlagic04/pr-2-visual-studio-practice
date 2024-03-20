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

	void PlayField::printPlayField(const tetromino::Points& tetromino, const bool showSpawnArea) const noexcept {
		printPlayFieldBorderLine();

		for (std::size_t i = (showSpawnArea)? 0 : spawnAreaHeight; i < getPlayFieldHeight(); ++i) {
			if (showSpawnArea && i == spawnAreaHeight) {
				printPlayFieldBorderLine();
			}

			utils::printTextWithBgColor(playFieldBlock, borderColor);
			
			for (std::size_t ii = 0; ii < m_playField[i].size(); ++ii) {
				if (tetromino.doesPointExist({ i, ii })) {
					utils::printTextWithBgColor(playFieldBlock, tetromino.getPointsColor());
				}
				else {
					utils::printTextWithBgColor(playFieldBlock, m_playField[i][ii]);
				}
			}

			utils::printTextWithBgColor(playFieldBlock, borderColor);
			std::cout << '\n';
		}

		printPlayFieldBorderLine();
	}

	void PlayField::printPlayField(const bool showSpawnArea) const noexcept {
		printPlayFieldBorderLine();

		for (std::size_t i = (showSpawnArea) ? 0 : spawnAreaHeight; i < getPlayFieldHeight(); ++i) {
			if (showSpawnArea && i == spawnAreaHeight) {
				printPlayFieldBorderLine();
			}

			utils::printTextWithBgColor(playFieldBlock, borderColor);

			for (std::size_t ii = 0; ii < m_playField[i].size(); ++ii) {
				utils::printTextWithBgColor(playFieldBlock, m_playField[i][ii]);
			}

			utils::printTextWithBgColor(playFieldBlock, borderColor);
			std::cout << '\n';
		}

		printPlayFieldBorderLine();
	}

	bool PlayField::isPlayFieldDefaultAt(const tetromino::Points::PointType& point) const noexcept {
		return m_playField[point.first][point.second] == TerminalBgColor::Default;
	}

	bool PlayField::isPointInPlayField(const tetromino::Points::PointType& point) const noexcept {
		return point.first >= 0 && point.first < static_cast<std::ptrdiff_t>(getPlayFieldHeight())
			&& point.second >= 0 && point.second < static_cast<std::ptrdiff_t>(getPlayFieldWidth());
	}

	bool PlayField::canTetrominoMoveDown(const tetromino::Points& tetromino) const noexcept {
		for (const auto& point : tetromino) {
			const std::size_t row = point.first + 1;

			if (row == getPlayFieldHeight() || !isPlayFieldDefaultAt({ row, point.second })) {
				return false;
			}
		}

		return true;
	}

	bool PlayField::canTetrominoMoveLeft(const tetromino::Points& tetromino) const noexcept {
		for (const auto& point : tetromino) {
			const std::ptrdiff_t col = point.second - 1;

			if (col == -1 || !isPlayFieldDefaultAt({ point.first, col })) {
				return false;
			}
		}

		return true;
	}

	bool PlayField::canTetrominoMoveRight(const tetromino::Points& tetromino) const noexcept {
		for (const auto& point : tetromino) {
			const std::size_t col = point.second + 1;

			if (col == getPlayFieldWidth() || !isPlayFieldDefaultAt({ point.first, col })) {
				return false;
			}
		}

		return true;
	}

	bool PlayField::canTetrominoBeRotated(const tetromino::Points& tetromino) const noexcept {
		for (const auto& point : tetromino) {
			if (!isPointInPlayField(point) || !isPlayFieldDefaultAt(point)) {
				return false;
			}
		}

		return true;
	}

	void PlayField::rotateTetromino(tetromino::Points& tetromino, const bool rotateRight) noexcept {
		auto currentTetrominoCopy{ tetromino };

		if (rotateRight) {
			currentTetrominoCopy.rotateRight();
		}
		else {
			currentTetrominoCopy.rotateLeft();
		}

		if (!canTetrominoBeRotated(currentTetrominoCopy)) {
			return;
		}

		tetromino = std::move(currentTetrominoCopy);
	}

	// protected members below

	void PlayField::spawnTetrominoOnPlayField(tetromino::Points& tetromino) noexcept {
		tetromino.offsetAllPointsBy({ 1, 3 });
	}

	void PlayField::moveTetrominoDown(tetromino::Points& tetromino) {
		for (auto& point : tetromino) {
			++point.first;
		}
		tetromino.moveOffsetDown();
	}

	void PlayField::setPlayFieldPoint(const std::size_t row, const std::size_t col, const TerminalBgColor bgColor) noexcept {
		m_playField[row][col] = bgColor;
	}

	void PlayField::drawTetromino(const tetromino::Points& tetromino) noexcept {
		for (const auto& point : tetromino) {
			setPlayFieldPoint(point.first, point.second, tetromino.getPointsColor());
		}
	}

	bool PlayField::wasSpawnLineCrossed() const noexcept {
		return !std::all_of(m_playField[spawnAreaHeight - 1].begin(), m_playField[spawnAreaHeight - 1].end(),
			[](const auto color) {
				return color == TerminalBgColor::Default;
			}
		);
	}

	std::size_t PlayField::removeFullRows() noexcept {
		std::size_t counter{ 0 };
		std::size_t totalCounter{ 0 };

		auto moveRowsDown = [&](const std::size_t index) {
			for (std::ptrdiff_t start = index - counter - 1; start >= 0; --start) {
				m_playField[start + counter] = m_playField[start];
			}
			for (std::size_t start = 0; start < counter; ++start) {
				m_playField[start] = std::vector<TerminalBgColor>(getPlayFieldWidth(), TerminalBgColor::Default);
			}
		};

		for (std::size_t i = 0; i < m_playField.size(); ++i) {
			auto isBgColorDifferentThanDefault = [&](const TerminalBgColor bgColor) { return bgColor != TerminalBgColor::Default; };
			auto isRowFilled = [&]() { return std::all_of(m_playField[i].begin(), m_playField[i].end(), isBgColorDifferentThanDefault); };

			if (isRowFilled()) {
				counter++;
			}
			else {
				moveRowsDown(i);

				totalCounter += counter;
				counter = 0;
			}
		}

		moveRowsDown(m_playField.size());
		
		return totalCounter + counter;
	}

	// private members below

	void PlayField::printPlayFieldBorderLine() const noexcept {
		// The + 2 in the condition is for it to take into account the sides
		// you can remove it to see it's effects better
		for (std::size_t i = 0; i < m_playField[0].size() + 2; ++i) {
			utils::printTextWithBgColor(playFieldBlock, borderColor);
		}
		std::cout << '\n';
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
		printGameIntroInfo();
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
		std::cout << "J key moves things left, L key moves things right\n";
		std::cout << "Q and E are used to rotate the pieces 90 deg left or right\n";
		std::cout << "When you've read and understood all of this press any key to start the game...";
		std::cin.get();

		utils::clearScreen();
	}

	void TetrisGame::startMainGameLoop() {
		utils::clearScreenANSI();
		utils::turnOffCursor();

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

			handleKeyPressActions();

			const bool didEnoughTimePassForMove{ getCurrentMsPassed() >= msNeededFor1MoveDown };

			if (didEnoughTimePassForMove && !canTetrominoMoveDown(currentTetromino)) {
				setIsCurrentTetrominoLockedIn(true);
				setMsPassed(0);
				drawTetromino(currentTetromino);
				removeLastUsedTetromino();
				setLinesCleared(static_cast<int>(getLinesCleared() + removeFullRows()));

				if (isGameOver()) {
					break;
				}
			}
			else if (didEnoughTimePassForMove && canTetrominoMoveDown(currentTetromino)) {
				moveTetrominoDown(currentTetromino);
				setMsPassed(0);
			}
		}

		utils::clearScreen();
		utils::turnOnCursor();
		printLinesClearedInfo();
		printPlayField(true);

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

	void TetrisGame::handleKeyPressActions() noexcept {
		if (utils::isKeyPressed()) {
			const char keyPressed{ utils::getPressedKey() };

			if (m_keyPressEvents.find(keyPressed) != m_keyPressEvents.end()) {
				m_keyPressEvents.at(keyPressed)();
			}
		}
	}

	tetromino::Points& TetrisGame::getCurrentTetromino() noexcept {
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