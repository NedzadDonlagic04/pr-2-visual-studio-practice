#include"tetrisGame.hpp"
#include<iostream>

namespace tetris {
	TetrisGame::TetrisGame() {

	}

	void TetrisGame::run() {
		printGameIntroInfo();
		startMainGameLoop();
	}

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
	}

	void TetrisGame::startMainGameLoop() {
		std::cout << "Game started\n";
	}
}