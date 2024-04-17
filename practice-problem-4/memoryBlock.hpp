#ifndef _PRACTICE_PROBLEM_4_MEMORY_BLOCK_HPP
#define _PRACTICE_PROBLEM_4_MEMORY_BLOCK_HPP

#include"memoryError.hpp"
#include<optional>

namespace memory {
	// ----------------------------------------------
	// MemoryBlock declaration
	// ----------------------------------------------
	class [[nodiscard]] MemoryBlock {
	public:
		constexpr static unsigned int timeToConvertAllBitsTo1{ 100 };
		constexpr static unsigned int timeToConvert1To0{ 1 };
		constexpr static std::string_view timeConversionUnit{ "ns" };

		[[nodiscard]] bool isConvertableTo(const MemoryBlock&) const;
		[[nodiscard]] unsigned int getTimeInNsToConvertTo(const MemoryBlock&) const noexcept;
		
		MemoryBlock(const MemoryBlock&);
		MemoryBlock(MemoryBlock&&) noexcept;

		MemoryBlock& operator=(const MemoryBlock&);

		const char at(const std::size_t) const;
		
		[[nodiscard]] std::size_t size() const noexcept;
	private:
		std::string m_bits{};

		MemoryBlock(const std::string_view);

		[[nodiscard]] std::string& getBits() noexcept;
		[[nodiscard]] std::string_view getBits() const noexcept;

		[[nodiscard]] static bool areBitsAll0sAnd1s(const std::string_view) noexcept;
		char& operator[](const std::size_t);

		friend std::ostream& operator<<(std::ostream&, const MemoryBlock&) noexcept;

		friend std::optional<MemoryBlock> createMemoryBlock(
			const std::string_view,
			MemoryErrorHandler&
		) noexcept;
	};

	// friend function declaration
	std::ostream& operator<<(std::ostream&, const MemoryBlock&) noexcept;

	[[nodiscard]] std::optional<MemoryBlock> createMemoryBlock(
		const std::string_view,
		MemoryErrorHandler&
	) noexcept;
}

#endif
