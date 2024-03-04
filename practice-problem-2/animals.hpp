#ifndef PRACTICE_PROBLEM_2_ANIMALS_HPP
#define PRACTICE_PROBLEM_2_ANIMALS_HPP

#include<string>
#include<string_view>
#include<unordered_map>
#include<functional>
#include<random>

namespace animal {
	// -----------------------
	// Animal class declaration
	// -----------------------
	class Animal {
	public:
		Animal() = default;
		virtual ~Animal();

		[[nodiscard]] virtual float getAnimalPerformance() const = 0;
		[[nodiscard]] virtual std::string_view getAnimalName() const noexcept = 0;
		
		virtual void handleUserInput() = 0;
		virtual void generateData(std::mt19937&) = 0;
	private:
	};


	// -----------------------
	// Chicken class declaration
	// -----------------------
	class Chicken : public Animal {
	public:
		Chicken() = default;
		Chicken(const float);
		~Chicken() override;

		[[nodiscard]] float getEggsProducedPerDay() const noexcept;
		void setEggsProducedPerDay(const float) noexcept;

		[[nodiscard]] float getAnimalPerformance() const override;
		[[nodiscard]] std::string_view getAnimalName() const noexcept override;

		void handleUserInput() override;
		void generateData(std::mt19937&) override;

		constexpr static float CHICKEN_FACTOR{ 2.1f };
	private:
		float m_eggsProducedPerDay{};
	};


	// -----------------------
	// Cow class declaration
	// -----------------------
	class Cow : public Animal {
	public:
		Cow() = default;
		Cow(const float);
		~Cow() override;

		[[nodiscard]] float getLitersOfMilkMadePerDay() const noexcept;
		void setLitersOfMilkMadePerDay(const float) noexcept;

		[[nodiscard]] float getAnimalPerformance() const override;
		[[nodiscard]] std::string_view getAnimalName() const noexcept override;

		void handleUserInput() override;
		void generateData(std::mt19937&) override;

		constexpr static float COW_FACTOR{ 1.2f };
	private:
		float m_litersOfMilkMadePerDay{};
	};


	// -----------------------
	// Sheep class declaration
	// -----------------------
	class Sheep : public Animal {
	public:
		Sheep() = default;
		Sheep(const float);
		~Sheep() override;

		[[nodiscard]] float getGramsOfWoolMadePerDay() const noexcept;
		void setGramsOfWoolMadePerDay(const float) noexcept;

		[[nodiscard]] float getAnimalPerformance() const override;
		[[nodiscard]] std::string_view getAnimalName() const noexcept override;

		void handleUserInput() override;
		void generateData(std::mt19937&) override;

		constexpr static float SHEEP_FACTOR{ 1.7f };
	private:
		float m_gramsOfWoolMadePerDay{};
	};

	// -----------------------
	// constants definition
	// -----------------------
	inline const std::unordered_map<std::string, std::function<Animal*()>> ANIMAL_TYPES{
		{"chicken", []() { return new Chicken(); }},
		{"cow", []() { return new Cow(); }},
		{"sheep", []() { return new Sheep(); }},
	};

	// -----------------------
	// function declaration
	// -----------------------
	[[nodiscard]] bool isValidAnimalType(const std::string_view);
	void printAnimalTypes();

	[[nodiscard]] Animal** allocateArrayOfAnimals(const std::size_t);
	void deallocateArrayOfAnimals(Animal**&, const std::size_t);

	void enterAnimalType(std::string&);
	
	void enterAnimalsArray(Animal** const, const std::size_t);
	void enterAnimal(Animal*&);

	[[nodiscard]] Animal* generateRandomAnimal(std::mt19937&);
	void generateAnimalsArrayData(Animal** const, const std::size_t);

	void printAnimalsArray(const Animal* const * const, const std::size_t);

	void sortAnimalArray(Animal** const, const std::size_t, const bool = true);
}

#endif