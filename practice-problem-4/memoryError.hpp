#ifndef _PRACTICE_PROBLEM_4_MEMORY_ERROR
#define _PRACTICE_PROBLEM_4_MEMORY_ERROR

#include<ostream>
#include<string>
#include<string_view>

namespace memory {
	// ----------------------------------------------
	// MemoryErrorValue declaration and definition
	// ----------------------------------------------
	enum class MemoryErrorValue {
		Ok,
		MaxNumOfBitsExceeded,
		MinNumOfBitsExceeded,
		Non0And1CharFound,
		MemoryLinesNotSameSize,
		MemoryLinesDelimiterNotFound,
	};

	// ----------------------------------------------
	// MemoryError declaration
	// ----------------------------------------------
	class [[nodiscard]] MemoryErrorHandler {
	public:
		constexpr static int minNumOfBits{ 2 };
		constexpr static int maxNumOfBits{ 16 };

		MemoryErrorHandler() = default;

		[[nodiscard]] std::string getCurrentStateErrorMsg() const;

		operator bool() const noexcept;

		[[nodiscard]] MemoryErrorValue getState() const noexcept;
		
		void reset() noexcept;
		void setState(const MemoryErrorValue) noexcept;

		MemoryErrorValue operator=(const MemoryErrorValue) noexcept;
	private:
		MemoryErrorValue m_state{ MemoryErrorValue::Ok };

		friend std::ostream& operator<<(std::ostream&, const MemoryErrorHandler&) noexcept;
	};

	// friend function declaration
	std::ostream& operator<<(std::ostream&, const MemoryErrorHandler&) noexcept;

}

#endif 