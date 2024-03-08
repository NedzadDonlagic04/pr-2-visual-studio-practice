#include<iostream>
#include<algorithm>
#include"tetromino.hpp"

int main() {
	auto terminosCopy{ tetromino::tetrominos };

	std::for_each(
		terminosCopy.begin(),
		terminosCopy.end(),
		[](auto& tetromino) {
			tetromino::printAllRotationsOfATetromino(tetromino);
		}
	);

	return 0;
}