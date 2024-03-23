#include<iostream>
#include"fraction.hpp"

int main() {
	fraction::Fraction foo{ 5, 2 };

	std::cout << "foo original: " << foo << '\n';

	foo.setNumerator(-23);
	std::cout << "foo after setNumerator(-23): " << foo << '\n';

	foo.setDenominator(-3);
	std::cout << "foo after setDenominator(-2): " << foo << '\n';

	std::cout << "foo getResultOfDivision(): " << foo.getResultOfDivision() << '\n';
	std::cout << "foo getResultOfDivision(4): " << foo.getResultOfDivision(4) << '\n';

	return 0;
}