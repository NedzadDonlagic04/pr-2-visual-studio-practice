#ifndef _PRACTICE_PROBLEM_3_UTILS_HPP
#define _PRACTICE_PROBLEM_3_UTILS_HPP

#include<cstdint>
#include<stdexcept>
#include<cmath>
#include<string>
#include<string_view>
#include<iostream>

namespace utils {
	void printErrorMsg(const std::string_view) noexcept;
	void clearBuffer() noexcept;

	constexpr void swap(int& num1, int& num2) noexcept {
		num1 += num2;
		num2 = num1 - num2;
		num1 -= num2;
	}

	template<typename NumberType>
	[[nodiscard]] constexpr NumberType abs(const NumberType num) noexcept {
		static_assert(
			std::is_arithmetic_v<NumberType>,
			"utils::abs requires an arithmetic type\n"
		);

		return (num < static_cast<NumberType>(0)) ? -num : num;
	}

	[[nodiscard]] constexpr bool areEqual(const double num1, const double num2, const double epsilon = 0.01) {
		return abs(num1 - num2) < epsilon;
	}

	// Implements euclid's algorithm
	// https://en.wikipedia.org/wiki/Euclidean_algorithm
	[[nodiscard]] constexpr int getGreatestCommonDenominator(int num1, int num2) {
		num1 = abs(num1);
		num2 = abs(num2);

		if (num1 < num2) {
			swap(num1, num2);
		}

		while (num2) {
			swap(num1, num2);
			num2 %= num1;
		}

		return num1;
	}

	[[nodiscard]] constexpr int64_t getPowOf10(const int exponent) {
		if (exponent < 0) {
			throw std::invalid_argument("Negative exponent not allowed\n");
		}

		int64_t powOf10{ 1 };

		for (int i = 0; i < exponent; ++i, powOf10 *= 10);

		return powOf10;
	}

	[[nodiscard]] constexpr double round(double num) {
		if ((num - static_cast<int>(num)) >= 0.5) {
			++num;
		}

		num = static_cast<int>(num);

		return num;
	}

	template<typename NumberType>
	[[nodiscard]] constexpr double roundToNDecimals(const NumberType number, const int precision) {
		static_assert(
			std::is_floating_point_v<NumberType>,
			"utils::roundToNDecimals requires a floating point type\n"
		);

		if (precision < 0) {
			throw std::invalid_argument("Negative precision not allowed\n");
		}

		const auto powOf10{ getPowOf10(precision) };
			
		return round(number * powOf10) / powOf10;
	}

	template<typename Callback = bool(const std::string&)>
	void getStringInput(
		std::string& str,
		const std::string_view outputMsg,
		Callback isInputValid = [](const std::string&) { return true; }
	) noexcept {
		bool repeatLoop{};

		do {
			repeatLoop = false;

			std::cout << outputMsg;
			std::getline(std::cin >> std::ws, str);

			if (std::cin.fail()) {
				utils::printErrorMsg("Invalid string input\n");
				std::cin.clear();
				repeatLoop = true;
			}
			else if (!isInputValid(str)) {
				repeatLoop = true;
			}

		} while (repeatLoop);
	}
}

#endif