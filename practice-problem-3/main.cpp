#include<iostream>
#include"fraction.hpp"

int main() {
	fraction::Fraction fraction{};

	fraction::getFractionInput(fraction, "Enter fraction: ");

	return 0;
}