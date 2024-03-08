#ifndef _TETRIS_TETRIS_GAME_HPP
#define _TETRIS_TETRIS_GAME_HPP

namespace tetris {
	class TetrisGame {
	public:
		TetrisGame();

		void run();
	private:
		void printGameIntroInfo() const noexcept;
		void startMainGameLoop();
	};
}

#endif