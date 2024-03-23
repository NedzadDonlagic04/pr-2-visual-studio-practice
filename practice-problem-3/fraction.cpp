#include"fraction.hpp"

#include<iostream>

namespace fraction {
	// ---------------------------
	// Fraction class definition
	// ---------------------------
	// public
	Fraction::Fraction(const int numerator, const int denominator) {
		setNumerator(numerator);
		setDenominator(denominator);
	}

	Fraction::Fraction(const Fraction& fraction) noexcept 
		: m_numerator(fraction.m_numerator)
		, m_denominator(fraction.m_denominator)
		, m_fractionStr(fraction.m_fractionStr)
	{}

	Fraction::Fraction(Fraction&& fraction) noexcept
		: m_numerator(std::exchange(fraction.m_numerator, 1))
		, m_denominator(std::exchange(fraction.m_denominator, 1))
		, m_fractionStr(std::move(fraction.m_fractionStr))
	{}

	void Fraction::setNumerator(const int numerator) noexcept {
		m_numerator = numerator;
		
		updateNumeratorPartOfStr();
	}

	void Fraction::setDenominator(const int denominator) {
		if (!denominator) {
			throw std::invalid_argument("Denominator ca	n't be 0\n");
		}

		m_denominator = denominator;

		updateDenominatorPartOfStr();
	}

	int Fraction::getNumerator() const noexcept {
		return m_numerator;
	}

	int Fraction::getDenominator() const noexcept {
		return m_denominator;
	}

	double Fraction::getResultOfDivision(const int precision) const {
		if (precision < 0) {
			throw std::invalid_argument("Negative precision not allowed\n");
		}

		const double resultOfDivison{ static_cast<double>(getNumerator()) / getDenominator() };

		return utils::roundToNDecimals(resultOfDivison, precision);
	}

	std::string_view Fraction::getStrView() const noexcept {
		return m_fractionStr;
	}

	std::ostream& operator<<(std::ostream& os, const Fraction& fraction) noexcept {
		os << fraction.getStrView();

		return os;
	}

	std::istream& operator>>(std::istream& is, Fraction& fraction) noexcept {
		int numerator{};
		int denominator{};
		char line{};

		std::cin >> numerator >> line >> denominator;

		if (line != '/') {
			is.setstate(std::ios::failbit);
		} else if (std::cin.good()) {
			fraction.setNumerator(numerator);
			fraction.setDenominator(denominator);
		}

		return is;
	}

	// private
	void Fraction::updateNumeratorPartOfStr() noexcept {
		const std::size_t lineIndex { m_fractionStr.find('/') };
		
		m_fractionStr = std::to_string(getNumerator()) + m_fractionStr.substr(lineIndex);
	}

	void Fraction::updateDenominatorPartOfStr() noexcept {
		const std::size_t lineIndex{ m_fractionStr.find('/') };

		m_fractionStr = m_fractionStr.substr(0, lineIndex + 1) + std::to_string(getDenominator());
	}
}