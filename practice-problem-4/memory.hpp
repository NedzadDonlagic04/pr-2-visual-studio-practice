#ifndef _PRACTICE_PROBLEM_4_MEMORY_HPP
#define _PRACTICE_PROBLEM_4_MEMORY_HPP

#include<string>
#include<random>

/*
	A memory block is
	1111
	A memory line is
	1111|0110|1000
	A memory conversion line is 
	1111|0110|1000 -> 1011|0000|1010 

	These were the names I came up while I was working so
	if there are some inconsistencies, that's my bad
*/

namespace memory {
	[[nodiscard]] std::string generateMemoryBlock(std::mt19937&);
	[[nodiscard]] std::string generateMemoryBlock(std::mt19937&, int);

	[[nodiscard]] std::string generateMemoryLineStr(std::mt19937&);
	[[nodiscard]] std::string generateMemoryLineStr(std::mt19937&, const int, const int);

	[[nodiscard]] std::string generateConversionLineStr(std::mt19937&);
	[[nodiscard]] std::string generateConversionLineStr(std::mt19937&, const int, const int);
}

#endif