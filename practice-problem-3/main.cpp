#include<iostream>
#include"fraction.hpp"

int main() {
	fraction::Fraction fraction1{ "1/4" };
	fraction::Fraction fraction2{ "6/3" };

	std::cout << fraction1 - fraction2 << '\n';

	return 0;
}