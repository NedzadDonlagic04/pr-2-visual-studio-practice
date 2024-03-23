#include<iostream>
#include"fraction.hpp"

int main() {
	fraction::Fraction fraction{ "1/-5" };

	for (int i = 0; i < 4; ++i) {
		std::cout << fraction << " = " << fraction.getResultOfDivision() << '\n';
		++fraction;
	}
	std::cout << '\n';

	fraction = { 4, 5 };

	for (int i = 0; i < 4; ++i) {
		std::cout << fraction << " = " << fraction.getResultOfDivision() << '\n';
		--fraction;
	}
	std::cout << '\n';

	return 0;
}