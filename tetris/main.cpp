#include<iostream>
#include"tetrisGame.hpp"
#include"tetromino.hpp"

int main() {
    tetris::TetrisGame tetrisGame{};

    tetrisGame.run();

    return 0;
}