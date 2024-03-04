#include"utils.hpp"
#include<limits>
#include<cmath>
#include<algorithm>

namespace utils {
	void printErrorMsg(std::string_view errorMsg) {
		std::cout << "\033[31m";
		std::cout << errorMsg;
		std::cout << "\033[37m";
	}

	void clearBuffer() {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	void printBreakLine() {
		std::cout << "---------------------------------------------------------\n";
	}

	void enterText(std::string& str, std::string_view outputMsg) {
		do {
			if (std::cin.fail()) {
				clearBuffer();
				printErrorMsg("Invalid text input\n");
			}

			std::cout << outputMsg;
			std::getline(std::cin >> std::ws, str);
		} while (std::cin.fail());
	}

	void toLower(std::string& str) {
		std::for_each(str.begin(), str.end(), [](char& c) { c = std::tolower(c); });
	}

	float roundToNDecimals(const float num, const int precision) {
		const double powOf10{ std::pow(10, std::max(0, precision)) };

		return static_cast<float>(std::round(num * powOf10) / powOf10);
	}
}