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

	Fraction::Fraction(const Fraction& fraction) noexcept {
		setNumerator(fraction.getNumerator());
		setDenominator(fraction.getDenominator());
	}

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
		return fractionStr;
	}

	std::ostream& operator<<(std::ostream& os, const Fraction& fraction) noexcept {
		os << fraction.getStrView();

		return os;
	}

	std::istream& operator>>(std::istream& is, Fraction& fraction) noexcept {
		int numerator{};
		int denominator{};

		std::cin >> numerator;
		std::cin.ignore();
		std::cin >> denominator;

		if (std::cin.good()) {
			fraction.setNumerator(numerator);
			fraction.setDenominator(denominator);
		}

		return is;
	}

	// private
	void Fraction::updateNumeratorPartOfStr() noexcept {
		const std::size_t lineIndex { fractionStr.find('/') };
		
		fractionStr = std::to_string(getNumerator()) + fractionStr.substr(lineIndex);
	}

	void Fraction::updateDenominatorPartOfStr() noexcept {
		const std::size_t lineIndex{ fractionStr.find('/') };

		fractionStr = fractionStr.substr(0, lineIndex + 1) + std::to_string(getDenominator());
	}
}