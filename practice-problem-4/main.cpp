#include<iostream>

#include"memory.hpp"
#include"memoryConversionLine.hpp"

#include<random>

int main() {
	std::random_device dev{};
	std::mt19937 rng{ dev() };

	memory::MemoryErrorHandler errorHandler{};

	for (int i = 1; i <= 5; ++i) {
		const auto conversionLine{ memory::generateConversionLineStr(rng, 3, 3) };

		const auto memoryConversionLine{
			memory::createMemoryConversionLine(conversionLine, errorHandler)
		};

		if (!errorHandler) {
			std::cout << errorHandler << '\n';
			return -1;
		}

		std::cout << "Conversion " << i << ": ";
		std::cout << memoryConversionLine.value() << '\n';
		std::cout << "Conversion Time: ";
		std::cout << memoryConversionLine.value().getTimeInNsToConvertTo();
		std::cout << memory::MemoryBlock::timeConversionUnit << "\n\n";
	}

	return 0;
}