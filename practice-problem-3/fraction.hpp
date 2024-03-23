#ifndef _PRACTICE_PROBLEM_3_FRACTION_HPP
#define _PRACTICE_PROBLEM_3_FRACTION_HPP

#include"utils.hpp"

#include<string_view>
#include<string>

namespace fraction {
	// ---------------------------
	// Fraction class declaration
	// ---------------------------
	class Fraction {
	public:
		Fraction() = default;
		Fraction(const int, const int);
		Fraction(const Fraction&) noexcept;
		Fraction(Fraction&&) noexcept;

		void setNumerator(const int) noexcept;
		void setDenominator(const int);

		[[nodiscard]] int getNumerator() const noexcept;
		[[nodiscard]] int getDenominator() const noexcept;
		[[nodiscard]] double getResultOfDivision(const int = 2) const;
		[[nodiscard]] std::string_view getStrView() const noexcept;

		friend std::ostream& operator<<(std::ostream&, const Fraction&) noexcept;
		friend std::istream& operator>>(std::istream&, Fraction&) noexcept;
	
	private:
		int m_numerator{ 1 };
		int m_denominator{ 1 };
		std::string m_fractionStr{ "1/1" };
		
		void updateNumeratorPartOfStr() noexcept;
		void updateDenominatorPartOfStr() noexcept;
	};
}
#endif