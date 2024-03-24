#include"utils.hpp"

#include<iostream>

/*
	ANSI related content found on the link below
	https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
*/

namespace utils {
	void printErrorMsg(const std::string_view errorMsg) noexcept {
		std::cerr << "\033[31m";
		std::cerr << errorMsg;
		std::cerr << "\033[37m";
	}
}