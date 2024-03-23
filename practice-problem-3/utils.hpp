#ifndef _PRACTICE_PROBLEM_3_UTILS_HPP
#define _PRACTICE_PROBLEM_3_UTILS_HPP

#include<cstdint>
#include<stdexcept>
#include<cmath>

namespace utils {
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
			"roundToNDecimals requires a floating point type\n"
		);

		if (precision < 0) {
			throw std::invalid_argument("Negative precision not allowed\n");
		}

		const auto powOf10{ getPowOf10(precision) };
			
		return round(number * powOf10) / powOf10;
	}
}

#endif