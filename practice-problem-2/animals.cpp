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

	float Chicken::getEggsProducedPerDay() const noexcept {
		return m_eggsProducedPerDay;
	}

	void Chicken::setEggsProducedPerDay(const float eggsProducedPerDay) noexcept {
		m_eggsProducedPerDay = eggsProducedPerDay;
	}

	float Chicken::getAnimalPerformance() const {
		return m_eggsProducedPerDay * CHICKEN_FACTOR;
	}

	std::string_view Chicken::getAnimalName() const noexcept {
		return "chicken";
	}


	void Chicken::handleUserInput() {
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

		setEggsProducedPerDay(eggsProducedPerDay);
	}

	void Chicken::generateData(std::mt19937& rng) {
		std::uniform_real_distribution<float> eggsProducedPerDayDist(0, 8);

		const float eggsProducedPerDay{ eggsProducedPerDayDist(rng) };

		setEggsProducedPerDay(utils::roundToNDecimals(eggsProducedPerDay, 2));
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

	float Cow::getLitersOfMilkMadePerDay() const noexcept {
		return m_litersOfMilkMadePerDay;
	}

	void Cow::setLitersOfMilkMadePerDay(const float litersOfMilkMadePerDay) noexcept {
		m_litersOfMilkMadePerDay = litersOfMilkMadePerDay;
	}

	float Cow::getAnimalPerformance() const {
		return m_litersOfMilkMadePerDay * COW_FACTOR;
	}

	std::string_view Cow::getAnimalName() const noexcept {
		return "cow";
	}

	void Cow::handleUserInput() {
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

		setLitersOfMilkMadePerDay(litersOfMilkMadePerDay);
	}

	void Cow::generateData(std::mt19937& rng) {
		std::uniform_real_distribution<float> litersOfMilkProducedPerDayDist(0, 80);

		const float litersOfMilkMadePerDay{ litersOfMilkProducedPerDayDist(rng) };

		setLitersOfMilkMadePerDay(utils::roundToNDecimals(litersOfMilkMadePerDay, 2));
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

	float Sheep::getGramsOfWoolMadePerDay() const noexcept {
		return m_gramsOfWoolMadePerDay;
	}

	void Sheep::setGramsOfWoolMadePerDay(const float gramsOfWoolMadePerDay) noexcept {
		m_gramsOfWoolMadePerDay = gramsOfWoolMadePerDay;
	}

	float Sheep::getAnimalPerformance() const {
		return m_gramsOfWoolMadePerDay * SHEEP_FACTOR;
	}

	std::string_view Sheep::getAnimalName() const noexcept {
		return "sheep";
	}

	void Sheep::handleUserInput() {
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

		setGramsOfWoolMadePerDay(gramsOfWoolMadePerDay);
	}

	void Sheep::generateData(std::mt19937& rng) {
		std::uniform_real_distribution<float> gramsOfWoolMadePerDayDist(0, 80);

		const float gramsOfWoolMadePerDay{ gramsOfWoolMadePerDayDist(rng) };

		setGramsOfWoolMadePerDay(utils::roundToNDecimals(gramsOfWoolMadePerDay, 2));
	}

	// -----------------------
	// function definition / implementation
	// -----------------------
	bool isValidAnimalType(const std::string_view animalType) {
		for (const auto& ANIMAL_TYPE : ANIMAL_TYPES) {
			if (ANIMAL_TYPE.first == animalType) {
				return true;
			}
		}
		return false;
	}

	void printAnimalTypes() {
		std::cout << "Available animal types: ";
		char space[]{ 0, 0, 0 };
		for (const auto& ANIMAL_TYPE : ANIMAL_TYPES) {
			std::cout << space << ANIMAL_TYPE.first;
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
		utils::printBreakLine();
		for (std::size_t i = 0; i < size; i++) {
			std::cout << "Enter animal number " << i + 1 << " info\n";
			enterAnimal(animals[i]);
			std::cout << '\n';
		}
		utils::printBreakLine();
	}

	void enterAnimal(Animal*& animal) {
		std::string animalType{};
		
		enterAnimalType(animalType);

		const auto createAnimal{ ANIMAL_TYPES.at(animalType) };
		
		animal = createAnimal();

		animal->handleUserInput();
	}

	Animal* generateRandomAnimal(std::mt19937& rng) {
		std::uniform_int_distribution<std::size_t> animalIndexDist(0, ANIMAL_TYPES.size() - 1);
		std::size_t index{ 0 };
		std::size_t indexToFind{ animalIndexDist(rng) };

		for (const auto& ANIMAL_TYPE : ANIMAL_TYPES) {
			if (index == indexToFind) {
				return ANIMAL_TYPE.second();
			}

			index++;
		}
		return nullptr;
	}

	void generateAnimalsArrayData(Animal** const animals, const std::size_t size) {
		std::random_device dev{};
		std::mt19937 rng{ dev() };

		for (std::size_t i = 0; i < size; i++) {
			animals[i] = generateRandomAnimal(rng);
			animals[i]->generateData(rng);
		}
	}

	void printAnimalsArray(const Animal* const* const animals, const std::size_t size) {
		utils::printBreakLine();
		
		const auto originalPrecision{ std::cout.precision() };
		std::cout << std::setprecision(2) << std::fixed;

		for (std::size_t i = 0; i < size; i++) {
			std::cout << "Animal number " << i + 1 << " info\n";
			std::cout << "Animal type: " << std::quoted(animals[i]->getAnimalName()) << '\n';
			std::cout << "Animal performance: " << animals[i]->getAnimalPerformance() << '\n';
			std::cout << '\n';
		}

		std::cout << std::setprecision(originalPrecision) << std::defaultfloat;

		utils::printBreakLine();
	}

	// Implements insertion sort
	void sortAnimalArray(Animal** const animals, const std::size_t size, const bool sortDesc) {
		for (std::size_t i = 1; i < size; i++) {
			for (std::ptrdiff_t ii = i; ii >= 1; ii--) {
				const float& currAnimalPerformance{ animals[ii]->getAnimalPerformance() };
				const float& prevAnimalPerformance{ animals[ii - 1]->getAnimalPerformance() };
				if (sortDesc && currAnimalPerformance > prevAnimalPerformance) {
					std::swap(animals[ii], animals[ii - 1]);
				}
				else if (!sortDesc && currAnimalPerformance < prevAnimalPerformance) {
					std::swap(animals[ii], animals[ii - 1]);
				}
			}
		}
	}
}