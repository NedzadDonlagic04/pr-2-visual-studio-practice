#include"memoryBlock.hpp"

#include<algorithm>

namespace memory {
	// ----------------------------------------------
	// MemoryBlock definitions
	// ----------------------------------------------
	//public
	MemoryBlock::MemoryBlock(const MemoryBlock& memoryBlock)
		: m_bits{ memoryBlock.getBits() }
	{}

	MemoryBlock::MemoryBlock(MemoryBlock&& memoryBlock) noexcept
		: m_bits{ std::move(memoryBlock.getBits()) }
	{}

	bool MemoryBlock::isConvertableTo(const MemoryBlock& memoryBlock) const {
		return size() == memoryBlock.size();
	}

	unsigned int MemoryBlock::getTimeInNsToConvertTo(const MemoryBlock& target) const noexcept {
		MemoryBlock thisCopy{ *this };

		unsigned int totalConversionTime{ 0 };

		for (std::size_t i = 0; i < size(); ++i) {
			if (thisCopy[i] == '0' && target.at(i) == '1') {
				std::fill(begin(thisCopy.m_bits), end(thisCopy.m_bits), '1');
				totalConversionTime += timeToConvertAllBitsTo1;
				break;
			}
		}

		for (std::size_t i = 0; i < size(); ++i) {
			if (thisCopy[i] == '1' && target.at(i) == '0') {
				thisCopy[i] = '0';
				totalConversionTime += timeToConvert1To0;
			}
		}

		return totalConversionTime;
	}

	MemoryBlock& MemoryBlock::operator=(const MemoryBlock& rhs) {
		m_bits = rhs.m_bits;

		return *this;
	}

	const char MemoryBlock::at(const std::size_t index) const {
		return m_bits.at(index);
	}

	std::size_t MemoryBlock::size() const noexcept {
		return m_bits.size();
	}

	//private
	MemoryBlock::MemoryBlock(const std::string_view bits) 
		: m_bits { bits }
	{}

	std::string& MemoryBlock::getBits() noexcept {
		return m_bits;
	}

	std::string_view MemoryBlock::getBits() const noexcept {
		return m_bits;
	}

	bool MemoryBlock::areBitsAll0sAnd1s(const std::string_view bits) noexcept {
		for (const auto bit : bits) {
			if (bit != '0' && bit != '1') {
				return false;
			}
		}

		return true;
	}

	char& MemoryBlock::operator[](const std::size_t index) {
		return m_bits.at(index);
	}

	// friend function definitions
	std::ostream& operator<<(std::ostream& os, const MemoryBlock& memoryBlock) noexcept {
		os << memoryBlock.m_bits;

		return os;
	}

	std::optional<MemoryBlock> createMemoryBlock(
		const std::string_view bits, 
		MemoryErrorHandler& errorHandler
	) noexcept {
		if (!MemoryBlock::areBitsAll0sAnd1s(bits)) {
			errorHandler = MemoryErrorValue::Non0And1CharFound;
			return {};
		}
		else if (bits.size() < MemoryErrorHandler::minNumOfBits) {
			errorHandler = MemoryErrorValue::MinNumOfBitsExceeded;
			return {};
		}
		else if (bits.size() > MemoryErrorHandler::maxNumOfBits) {
			errorHandler = MemoryErrorValue::MaxNumOfBitsExceeded;
			return {};
		}

		return MemoryBlock(bits);
	}
}