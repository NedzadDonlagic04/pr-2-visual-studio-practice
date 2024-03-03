#include"animals.hpp"
#include"utils.hpp"
#include<iostream>
#include<iomanip>

namespace animal {
	// -----------------------
	// Animal class definition
	// -----------------------
	Animal::~Animal() {
		// Debugging
		// std::cout << "Animal destructor called\n";
	}


	// -----------------------
	// Chicken class definition
	// -----------------------
	Chicken::Chicken(const float eggsProducedPerDay)
		: m_eggsProducedPerDay(eggsProducedPerDay)
	{}

	Chicken::~Chicken() {
		// Debugging
		// std::cout << "Chicken destructor called\n";
	}

	float Chicken::getAnimalPerformance() const {
		return m_eggsProducedPerDay * CHICKEN_FACTOR;
	}

	std::string_view Chicken::getAnimalName() const noexcept {
		return ANIMAL_TYPES.at("chicken");
	}

	// -----------------------
	// Cow class definition
	// -----------------------
	Cow::Cow(const float litersOfMilkMadePerDay)
		: m_litersOfMilkMadePerDay(litersOfMilkMadePerDay)
	{}

	Cow::~Cow() {
		// Debugging
		// std::cout << "Cow destructor called\n";
	}

	float Cow::getAnimalPerformance() const {
		return m_litersOfMilkMadePerDay * COW_FACTOR;
	}

	std::string_view Cow::getAnimalName() const noexcept {
		return ANIMAL_TYPES.at("cow");
	}

	// -----------------------
	// Sheep class definition
	// -----------------------
	Sheep::Sheep(const float gramsOfWoolMadePerDay)
		: m_gramsOfWoolMadePerDay(gramsOfWoolMadePerDay)
	{}

	Sheep::~Sheep() {
		// Debugging
		// std::cout << "Sheep destructor called\n";
	}

	float Sheep::getAnimalPerformance() const {
		return m_gramsOfWoolMadePerDay * SHEEP_FACTOR;
	}

	std::string_view Sheep::getAnimalName() const noexcept {
		return ANIMAL_TYPES.at("sheep");
	}

	// -----------------------
	// function definition / implementation
	// -----------------------
	bool isValidAnimalType(const std::string_view animalType) {
		for (const auto& ANIMAL_TYPE : ANIMAL_TYPES) {
			if (ANIMAL_TYPE.second == animalType) {
				return true;
			}
		}
		return false;
	}

	void printAnimalTypes() {
		std::cout << "Available animal types: ";
		char space[]{ 0, 0, 0 };
		for (const auto & ANIMAL_TYPE : ANIMAL_TYPES) {
			std::cout << space << ANIMAL_TYPE.second;
			space[0] = ',';
			space[1] = ' ';
		}
		std::cout << '\n';
	}

	Animal** allocateArrayOfAnimals(const std::size_t size) {
		return new Animal * [size] {nullptr};
	}

	void deallocateArrayOfAnimals(Animal**& animals, const std::size_t size) {
		for (std::size_t i = 0; i < size; i++) {
			delete animals[i];
		}

		delete[] animals;
		animals = nullptr;
	}

	void enterAnimalType(std::string& animalType) {
		bool repeatLoop{};
		do {
			repeatLoop = false;

			printAnimalTypes();
			utils::enterText(animalType, "Enter animal type: ");
			utils::toLower(animalType);

			if (!isValidAnimalType(animalType)) {
				repeatLoop = true;
				utils::printErrorMsg("Invalid animal type\n");
			}
		} while (repeatLoop);
	}

	void enterAnimalsArray(Animal** const animals, const std::size_t size) {
		for (std::size_t i = 0; i < size; i++) {
			utils::printBreakLine();
			std::cout << "Enter animal number " << i + 1 << " info\n";
			enterAnimalsArray(animals[i]);
			utils::printBreakLine();
		}
	}

	Chicken* createChicken() {
		float eggsProducedPerDay{};

		utils::enterNum(eggsProducedPerDay, "Enter eggs made per day by the chicken: ",
			[](const float num) {
				if (num < 0 || num > 8) {
					utils::printErrorMsg("Entered amount has to be between 0 and 8\n");
					return false;
				}
				return true;
			}
		);

		return new Chicken(eggsProducedPerDay);
	}

	Cow* createCow() {
		float litersOfMilkMadePerDay{};

		utils::enterNum(litersOfMilkMadePerDay, "Enter liters of milk made per day by the cow: ",
			[](const float num) {
				if (num < 0 || num > 80) {
					utils::printErrorMsg("Entered amount has to be between 0 and 80\n");
					return false;
				}
				return true;
			}
		);

		return new Cow(litersOfMilkMadePerDay);
	}

	Sheep* createSheep() {
		float gramsOfWoolMadePerDay{};

		utils::enterNum(gramsOfWoolMadePerDay, "Enter wool made in grams per day by the sheep: ",
			[](const float num) {
				if (num < 0 || num > 1000) {
					utils::printErrorMsg("Entered amount has to be between 0 and 1000\n");
					return false;
				}
				return true;
			}
		);

		return new Sheep(gramsOfWoolMadePerDay);
	}

	void enterAnimalsArray(Animal*& animal) {
		std::string animalType{};
		
		enterAnimalType(animalType);
		
		if (animalType == ANIMAL_TYPES.at("chicken")) {
			animal = createChicken();
		}
		else if (animalType == ANIMAL_TYPES.at("cow")) {
			animal = createCow();
		}	
		else {
			animal = createSheep();
		}
	}

	void printAnimalsArray(const Animal* const* const animals, const std::size_t size) {
		for (std::size_t i = 0; i < size; i++) {
			utils::printBreakLine();
			std::cout << "Animal number " << i + 1 << " info\n";
			std::cout << "Animal type: " << std::quoted(animals[i]->getAnimalName()) << '\n';
			std::cout << "Animal performance: " << animals[i]->getAnimalPerformance() << '\n';
			utils::printBreakLine();
		}
	}

	// Implements merge sort
	void sortAnimalArray(Animal** animals, const std::size_t size, const bool sortDesc) {

	}
}