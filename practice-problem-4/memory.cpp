#include"memory.hpp"
#include"memoryError.hpp"
#include"memoryLine.hpp"
#include"memoryConversionLine.hpp"

#include"utils.hpp"

#include<sstream>
	
namespace memory {
	std::string generateMemoryBlock(std::mt19937& rng) {
		std::uniform_int_distribution<> generateNumberOfBits{ 
			MemoryErrorHandler::minNumOfBits, MemoryErrorHandler::maxNumOfBits 
		};

		const int numberOfBits{ generateNumberOfBits(rng) };

		std::uniform_int_distribution<short> bitGenerator{ 0, 1 };

		std::ostringstream bitsStream{};

		for (int i = 0; i < numberOfBits; ++i) {
			bitsStream << static_cast<char>('0' + bitGenerator(rng));
		}

		return bitsStream.str();
	}

	std::string generateMemoryBlock(std::mt19937& rng, int numberOfBits) {
		numberOfBits = std::clamp(
			numberOfBits,
			MemoryErrorHandler::minNumOfBits,
			MemoryErrorHandler::maxNumOfBits
		);

		std::uniform_int_distribution<short> bitGenerator{ 0, 1 };
		
		std::ostringstream bitsStream{};

		for (int i = 0; i < numberOfBits; ++i) {
			bitsStream << static_cast<char>('0' + bitGenerator(rng));
		}

		return bitsStream.str();
	}

	std::string generateMemoryLineStr(std::mt19937& rng) {
		const int memoryBlocksSize{ utils::generateNumber(rng, 1, 5) };
		std::vector<int> acceptedBitSizes{ 1, 2, 4, 8, 16 };
		const int numberOfBits{ utils::getRandomElementFromVector(rng, acceptedBitSizes) };

		std::ostringstream memoryBlockStream{};

		for (int i = 0; i < memoryBlocksSize - 1; ++i) {
			memoryBlockStream << generateMemoryBlock(rng, numberOfBits);
			memoryBlockStream << MemoryLine::memoryBlocksDelimiter;
		}
		memoryBlockStream << generateMemoryBlock(rng, numberOfBits);

		return memoryBlockStream.str();
	}

	std::string generateMemoryLineStr(std::mt19937& rng, const int memoryBlocksSize, const int numberOfBits) {
		std::ostringstream memoryBlockStream{};

		for (int i = 0; i < memoryBlocksSize - 1; ++i) {
			memoryBlockStream << generateMemoryBlock(rng, numberOfBits);
			memoryBlockStream << MemoryLine::memoryBlocksDelimiter;
		}
		memoryBlockStream << generateMemoryBlock(rng, numberOfBits);

		return memoryBlockStream.str();
	}

	std::string generateConversionLineStr(std::mt19937& rng) {
		const int memoryBlocksSize{ utils::generateNumber(rng, 1, 5) };
		std::vector<int> acceptedBitSizes{ 1, 2, 4, 8, 16 };
		const int numberOfBits{ utils::getRandomElementFromVector(rng, acceptedBitSizes) };

		std::ostringstream memoryLines{};

		memoryLines << generateMemoryLineStr(rng, memoryBlocksSize, numberOfBits);
		memoryLines << MemoryConversionLine::memoryLinesDelimiter;
		memoryLines << generateMemoryLineStr(rng, memoryBlocksSize, numberOfBits);

		return memoryLines.str();
	}

	std::string generateConversionLineStr(std::mt19937& rng, const int memoryBlocksSize, const int numberOfBits) {
		std::ostringstream memoryLines{};

		memoryLines << generateMemoryLineStr(rng, memoryBlocksSize, numberOfBits);
		memoryLines << MemoryConversionLine::memoryLinesDelimiter;
		memoryLines << generateMemoryLineStr(rng, memoryBlocksSize, numberOfBits);

		return memoryLines.str();
	}
}