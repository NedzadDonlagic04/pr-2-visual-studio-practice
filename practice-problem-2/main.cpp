#include<iostream>
#include"utils.hpp"
#include"animals.hpp"
#include<memory>

int main() {
	std::size_t animalsSize{};

	utils::enterNum(animalsSize, "Enter animal amount: ",
		[](const std::size_t num) {
			if (num < 2 || num > 1000) {
				utils::printErrorMsg("Entered amount has to be between 2 and 1000\n");
				return false;
			}
			return true;
		}
	);

	auto farmAnimals{ animal::allocateArrayOfAnimals(animalsSize) };

	animal::enterAnimalsArray(farmAnimals, animalsSize);
	animal::printAnimalsArray(farmAnimals, animalsSize);

	animal::sortAnimalArray(farmAnimals, animalsSize);

	std::cout << "Printing animal info after sorting by performance (DESC)\n";
	animal::printAnimalsArray(farmAnimals, animalsSize);

	animal::deallocateArrayOfAnimals(farmAnimals, animalsSize);

	return 0;
}