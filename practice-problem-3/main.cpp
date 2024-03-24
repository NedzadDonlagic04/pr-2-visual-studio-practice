#include<iostream>
#include"fraction.hpp"

int main() {
	fraction::Fraction fraction1{};
	fraction::Fraction fraction2{};

	std::string option{};

	utils::getStringInput(
		option, 
		"Do you want to generate input (yes / no): ",
		[](const std::string& str) {
			if (str != "yes" && str != "no") {
				utils::printErrorMsg("Entered option has to be \"yes\" or \"no\"\n");
				return false;
			}
			return true;
		}
	);

	if (option == "yes") {
		std::mt19937 rng{ std::random_device()() };
		fraction1 = fraction::generateFraction(rng, { -10, 10 }, { -10, 10 });
		fraction1 = fraction::generateFraction(rng, { -10, 10 }, { -10, 10 });
	}
	else {
		fraction::getFractionInput(fraction1, "Enter fraction 1: ");
		fraction::getFractionInput(fraction2, "Enter fraction 2: ");
		std::cout << '\n';
	}

	std::cout << "Fraction 1: " << fraction1 << '\n';
	std::cout << "Fraction 2: " << fraction2 << '\n';

	if (fraction1 == fraction2) {
		std::cout << "Fraction 1 is and fraction 2 are the same\n";
	}
	else if (fraction1 < fraction2) {
		std::cout << "Fraction 1 is smaller than fraction 2\n";
	}
	else {
		std::cout << "Fraction 2 is smaller than fraction 1\n";
	}
	
	fraction::Fraction fractionAdd{};
	fraction::Fraction fractionSub{};
	fraction::Fraction fractionMul{};
	fraction::Fraction fractionDiv{};

	for (int i = 0; i < 5; ++i, ++fraction1, ++fraction2) {
		fractionAdd = fraction1 + fraction2;
		fractionSub = fraction1 - fraction2;
		fractionMul = fraction1 * fraction2;
		fractionDiv = fraction1 / fraction2;

		std::cout << "Math operator +, -, * and / in iteration " << i + 1 << ":\n";
		std::cout << fraction1 << " + " << fraction2 << " = " << fractionAdd << " \t-> " << fractionAdd.getResultOfDivision() << '\n';
		std::cout << fraction1 << " - " << fraction2 << " = " << fractionSub << " \t-> " << fractionSub.getResultOfDivision() << '\n';
		std::cout << fraction1 << " * " << fraction2 << " = " << fractionMul << " \t-> " << fractionMul.getResultOfDivision() << '\n';
		std::cout << fraction1 << " / " << fraction2 << " = " << fractionDiv << " \t-> " << fractionDiv.getResultOfDivision() << '\n';

		std::cout << '\n';
	}

	return 0;
}