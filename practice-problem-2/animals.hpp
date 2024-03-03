#ifndef PRACTICE_PROBLEM_2_ANIMALS_HPP
#define PRACTICE_PROBLEM_2_ANIMALS_HPP

#include<string>
#include<string_view>
#include<unordered_map>

namespace animal {
	// -----------------------
	// constants definition
	// -----------------------
	inline const std::unordered_map<std::string, std::string> ANIMAL_TYPES {
		{"chicken", "chicken"},
		{"cow", "cow"},
		{"sheep", "sheep"},
	};

	// -----------------------
	// Animal class declaration
	// -----------------------
	class Animal {
	public:
		Animal() = default;
		virtual ~Animal();

		[[nodiscard]] virtual float getAnimalPerformance() const = 0;
		[[nodiscard]] virtual std::string_view getAnimalName() const noexcept = 0;
	private:
	};


	// -----------------------
	// Chicken class declaration
	// -----------------------
	class Chicken : public Animal {
	public:
		Chicken(const float);
		~Chicken() override;

		[[nodiscard]] float getAnimalPerformance() const override;
		[[nodiscard]] std::string_view getAnimalName() const noexcept override;

		constexpr static float CHICKEN_FACTOR{ 2.1f };
	private:
		float m_eggsProducedPerDay{};
	};


	// -----------------------
	// Cow class declaration
	// -----------------------
	class Cow : public Animal {
	public:
		Cow(const float);
		~Cow() override;

		[[nodiscard]] float getAnimalPerformance() const override;
		[[nodiscard]] std::string_view getAnimalName() const noexcept override;

		constexpr static float COW_FACTOR{ 1.2f };
	private:
		float m_litersOfMilkMadePerDay{};
	};


	// -----------------------
	// Sheep class declaration
	// -----------------------
	class Sheep : public Animal {
	public:
		Sheep(const float);
		~Sheep() override;

		[[nodiscard]] float getAnimalPerformance() const override;
		[[nodiscard]] std::string_view getAnimalName() const noexcept override;

		constexpr static float SHEEP_FACTOR{ 1.7f };
	private:
		float m_gramsOfWoolMadePerDay{};
	};

	// -----------------------
	// function declaration
	// -----------------------
	[[nodiscard]] bool isValidAnimalType(const std::string_view);
	void printAnimalTypes();

	[[nodiscard]] Animal** allocateArrayOfAnimals(const std::size_t);
	void deallocateArrayOfAnimals(Animal**&, const std::size_t);

	void enterAnimalType(std::string&);

	[[nodiscard]] Chicken* createChicken();
	[[nodiscard]] Cow* createCow();
	[[nodiscard]] Sheep* createSheep();
	
	void enterAnimalsArray(Animal** const, const std::size_t);
	void enterAnimalsArray(Animal*&);

	void printAnimalsArray(const Animal* const * const, const std::size_t);

	void sortAnimalArray(Animal** const, const std::size_t, const bool = true);
}

#endif