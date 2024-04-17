#ifndef _PRACTICE_PROBLEM_4_UTILS_HPP
#define _PRACTICE_PROBLEM_4_UTILS_HPP

#include<vector>
#include<string_view>
#include<random>

namespace utils {
	template<typename NumberType>
	NumberType generateNumber(std::mt19937& rng, const NumberType min, const NumberType max) {
		std::uniform_int_distribution<NumberType> generator{ min, max };

		return generator(rng);
	}

	template<typename VectorElementType>
	VectorElementType getRandomElementFromVector(std::mt19937& rng, const std::vector<VectorElementType>& vec) {
		const std::size_t index{ generateNumber(rng, static_cast<std::size_t>(0), vec.size() - 1) };

		return vec[index];
	}

	std::vector<std::string_view> splitStrView(const std::string_view, const std::string_view);
}

#endif