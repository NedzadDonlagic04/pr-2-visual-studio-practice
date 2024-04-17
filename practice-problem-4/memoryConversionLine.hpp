#ifndef _PRACTICE_PROBLEM_4_MEMORY_CONVERSION_LINE_HPP
#define _PRACTICE_PROBLEM_4_MEMORY_CONVERSION_LINE_HPP

#include"memoryLine.hpp"

#include<utility>

namespace memory {
	// ----------------------------------------------
	// MemoryConversionLine declaration
	// ----------------------------------------------
	class [[nodiscard]] MemoryConversionLine {
	public:
		constexpr static std::string_view memoryLinesDelimiter{ " -> " };
		
		[[nodiscard]] unsigned int getTimeInNsToConvertTo() const noexcept;

		MemoryConversionLine& operator=(const MemoryConversionLine&);

		const MemoryLine& first() const noexcept;
		const MemoryLine& second() const noexcept;
	private:
		std::pair<MemoryLine, MemoryLine> m_memoryLines;

		MemoryConversionLine(std::pair<MemoryLine, MemoryLine>) noexcept;

		MemoryLine& first() noexcept;
		MemoryLine& second() noexcept;

		[[nodiscard]] std::pair<MemoryLine, MemoryLine>& getMemoryLines() noexcept;
		[[nodiscard]] const std::pair<MemoryLine, MemoryLine>& getMemoryLines() const noexcept;

		friend std::ostream& operator<<(std::ostream&, const MemoryConversionLine&) noexcept;

		friend std::optional<MemoryConversionLine> createMemoryConversionLine(
			const std::string_view,
			MemoryErrorHandler&
		) noexcept;
	};

	[[nodiscard]] std::optional<MemoryConversionLine> createMemoryConversionLine(
		const std::string_view,
		MemoryErrorHandler&
	) noexcept;
}

#endif
