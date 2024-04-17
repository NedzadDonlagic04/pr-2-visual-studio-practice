#include"memoryError.hpp"

namespace memory {
	// ----------------------------------------------
	// MemoryError declaration
	// ----------------------------------------------
	// public
	[[nodiscard]] std::string MemoryErrorHandler::getCurrentStateErrorMsg() const {
		switch (getState()) {
		case MemoryErrorValue::MaxNumOfBitsExceeded:
			return "Number of bits should be equal or smaller than " + std::to_string(maxNumOfBits);
		case MemoryErrorValue::MinNumOfBitsExceeded:
			return "Number of bits should be equal or bigger than " + std::to_string(minNumOfBits);
		case MemoryErrorValue::Non0And1CharFound:
			return "Character other than 0 and 1 found";
		case MemoryErrorValue::MemoryLinesNotSameSize:
			return "Memory lines aren't the same size";
		case MemoryErrorValue::MemoryLinesDelimiterNotFound:
			return "Memory lines delimiter not found";
		}

		return "Ok";
	}

	MemoryErrorHandler::operator bool() const noexcept {
		return m_state == MemoryErrorValue::Ok;
	}

	MemoryErrorValue MemoryErrorHandler::getState() const noexcept {
		return m_state;
	}
	
	void MemoryErrorHandler::reset() noexcept {
		m_state = MemoryErrorValue::Ok;
	}

	void MemoryErrorHandler::setState(const MemoryErrorValue state) noexcept {
		m_state = state;
	}

	MemoryErrorValue MemoryErrorHandler::operator=(const MemoryErrorValue state) noexcept {
		m_state = state;

		return m_state;
	}

	// friend function definition
	std::ostream& operator<<(std::ostream& os, const MemoryErrorHandler& memoryError) noexcept {
		os << memoryError.getCurrentStateErrorMsg();

		return os;
	}
}