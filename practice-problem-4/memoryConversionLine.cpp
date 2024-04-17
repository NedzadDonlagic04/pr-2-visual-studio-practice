#include"memoryConversionLine.hpp"

namespace memory {
	// ----------------------------------------------
	// MemoryConversionLine declaration
	// ----------------------------------------------
	// public
	unsigned int MemoryConversionLine::getTimeInNsToConvertTo() const noexcept {
		return first().getTimeInNsToConvertTo(second());
	}

	MemoryConversionLine& MemoryConversionLine::operator=(
		const MemoryConversionLine& memoryConversionLine
	) {
		m_memoryLines = memoryConversionLine.getMemoryLines();

		return *this;
	}

	const MemoryLine& MemoryConversionLine::first() const noexcept {
		return m_memoryLines.first;
	}

	const MemoryLine& MemoryConversionLine::second() const noexcept {
		return m_memoryLines.second;
	}

	// private
	MemoryConversionLine::MemoryConversionLine(std::pair<MemoryLine, MemoryLine> memoryLines) noexcept
		: m_memoryLines{ std::move(memoryLines) }
	{}

	MemoryLine& MemoryConversionLine::first() noexcept {
		return m_memoryLines.first;
	}

	MemoryLine& MemoryConversionLine::second() noexcept {
		return m_memoryLines.second;
	}

	std::pair<MemoryLine, MemoryLine>& MemoryConversionLine::getMemoryLines() noexcept {
		return m_memoryLines;
	}

	const std::pair<MemoryLine, MemoryLine>& MemoryConversionLine::getMemoryLines() const noexcept {
		return m_memoryLines;
	}

	// friend function definitions
	std::ostream& operator<<(
		std::ostream& os, 
		const MemoryConversionLine& memoryConversionLine
	) noexcept {
		os << memoryConversionLine.first();
		os << MemoryConversionLine::memoryLinesDelimiter;
		os << memoryConversionLine.second();

		return os;
	}

	std::optional<MemoryConversionLine> createMemoryConversionLine(
		const std::string_view memoryConversionLine,
		MemoryErrorHandler& errorHandler
	) noexcept {
		const std::size_t memoryLine1End{
			memoryConversionLine.find(MemoryConversionLine::memoryLinesDelimiter)
		};

		if (memoryLine1End == std::string_view::npos) {
			errorHandler = MemoryErrorValue::MemoryLinesDelimiterNotFound;
			return {};
		}

		const std::size_t memoryLine2Start{ 
			memoryLine1End + MemoryConversionLine::memoryLinesDelimiter.size()
		};

		const auto memoryLine1{ memoryConversionLine.substr(0, memoryLine1End) };
		const auto memoryLine2{
			memoryConversionLine.substr(memoryLine2Start)
		};

		if (memoryLine1.size() != memoryLine2.size()) {
			errorHandler = MemoryErrorValue::MemoryLinesNotSameSize;
			return {};
		}

		MemoryErrorHandler state{};
		const auto firstMemoryLine { createMemoryLine(memoryLine1, state) };
		
		if (!state) {
			errorHandler = state;
			return {};
		}
		
		state.reset();

		const auto secondMemoryLine{ createMemoryLine(memoryLine2, state) };
		
		if (!state) {
			errorHandler = state;
			return {};
		}

		return MemoryConversionLine(
			std::pair<MemoryLine, MemoryLine>(firstMemoryLine.value(), secondMemoryLine.value())
		);
	}
}