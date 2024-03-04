#ifndef PRACTICE_PROBLEM_2_UTILS_HPP
#define PRACTICE_PROBLEM_2_UTILS_HPP

#include<iostream>
#include<string>
#include<string_view>

namespace utils {
	void printErrorMsg(std::string_view);
	void clearBuffer();
	void printBreakLine();

	void enterText(std::string&, std::string_view);
	void toLower(std::string&);

	[[nodiscard]] float roundToNDecimals(const float, const int);

	template<typename NumberType, typename Callback = bool(const int)>
	void enterNum(NumberType& num, std::string_view outputMsg, Callback isNumberValid = [](const int) { return true; }) {
		bool repeatLoop{};

		do {
			repeatLoop = false;

			std::cout << outputMsg;
			std::cin >> num;

			if (std::cin.fail()) {
				repeatLoop = true;
				clearBuffer();
				printErrorMsg("Invalid number input\n");
			}
			else if (!isNumberValid(num)) {
				repeatLoop = true;
				clearBuffer();
			}

		} while (repeatLoop);

		clearBuffer();
	}
}

#endif