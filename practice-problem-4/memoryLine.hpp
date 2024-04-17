#ifndef _PRACTICE_PROBLEM_4_MEMORY_LINE_HPP
#define _PRACTICE_PROBLEM_4_MEMORY_LINE_HPP

#include"memoryError.hpp"
#include"memoryBlock.hpp"

#include<vector>

namespace memory {
	// ----------------------------------------------
	// MemoryLine declaration
	// ----------------------------------------------
	class [[nodiscard]] MemoryLine {
	public:
		constexpr static std::string_view memoryBlocksDelimiter{ "|" };
		
		[[nodiscard]] bool isConvertableTo(const MemoryLine&) const;
		[[nodiscard]] unsigned int getTimeInNsToConvertTo(const MemoryLine&) const noexcept;

		MemoryLine& operator=(const MemoryLine&);

		const MemoryBlock at(const std::size_t) const;

		[[nodiscard]] std::size_t size() const noexcept;
	private:
		std::vector<MemoryBlock> m_memoryBlocks{};
		
		MemoryLine(std::vector<MemoryBlock>) noexcept;

		[[nodiscard]] std::vector<MemoryBlock>& getMemoryBlocks() noexcept;
		[[nodiscard]] const std::vector<MemoryBlock>& getMemoryBlocks() const noexcept;
		
		MemoryBlock& operator[](const std::size_t);

		friend std::ostream& operator<<(std::ostream&, const MemoryLine&) noexcept;

		friend std::optional<MemoryLine> createMemoryLine(
			const std::string_view,
			MemoryErrorHandler&
		) noexcept;
	};

	// friend function declaration
	std::ostream& operator<<(std::ostream&, const MemoryLine&) noexcept;

	[[nodiscard]] std::optional<MemoryLine> createMemoryLine(
		const std::string_view,
		MemoryErrorHandler&
	) noexcept;
}

#endif