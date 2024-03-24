#include"fraction.hpp"

#include<iostream>
#include<sstream>

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

	Fraction::Fraction(std::string fractionStr) {
		std::istringstream buffer{ std::move(fractionStr) };

		int numerator{};
		int denominator{};
		char line{};

		buffer >> numerator >> line >> denominator;

		if (line != '/' || buffer.fail()) {
			throw std::invalid_argument("Invalid fraction string_view\n");
		}

		setNumerator(numerator);
		setDenominator(denominator);
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
		return m_fractionStr;
	}

	Fraction& Fraction::operator=(const Fraction& rhs) noexcept {
		m_numerator = rhs.m_numerator;
		m_denominator = rhs.m_denominator;
		m_fractionStr = rhs.m_fractionStr;

		return *this;
	}
	
	Fraction& Fraction::operator=(Fraction&& rhs) noexcept {
		m_numerator = std::exchange(rhs.m_numerator, 1);
		m_denominator = std::exchange(rhs.m_denominator, 1);
		m_fractionStr = std::move(rhs.m_fractionStr);

		return *this;
	}

	Fraction& Fraction::operator++() noexcept {
		setNumerator(getNumerator() + getDenominator());

		return *this;
	}

	Fraction Fraction::operator++(int) noexcept {
		const Fraction copy{ *this };

		setNumerator(getNumerator() + getDenominator());

		return copy;
	}

	Fraction& Fraction::operator--() noexcept {
		setNumerator(getNumerator() - getDenominator());

		return *this;
	}

	Fraction Fraction::operator--(int) noexcept {
		const Fraction copy{ *this };

		setNumerator(getNumerator() - getDenominator());

		return copy;
	}

	Fraction Fraction::operator+(const Fraction& rhs) const noexcept {
		const int numerator{ 
			getNumerator() * rhs.getDenominator() + rhs.getNumerator() * getDenominator()
		};
		const int denominator{ getDenominator() * rhs.getDenominator() };

		const auto gcd{
			utils::getGreatestCommonDenominator(numerator, denominator)
		};

		return Fraction{ numerator / gcd, denominator / gcd };
	}
	
	Fraction Fraction::operator-(const Fraction& rhs) const noexcept {
		const int numerator{
			getNumerator() * rhs.getDenominator() - rhs.getNumerator() * getDenominator()
		};
		const int denominator{ getDenominator() * rhs.getDenominator() };

		const auto gcd{
			utils::getGreatestCommonDenominator(numerator, denominator)
		};

		return Fraction{ numerator / gcd, denominator / gcd };
	}

	Fraction Fraction::operator*(const Fraction& rhs) const noexcept {
		const int numerator{ getNumerator() * rhs.getNumerator() };
		const int denominator{ getDenominator() * rhs.getDenominator() };

		const auto gcd{
			utils::getGreatestCommonDenominator(numerator, denominator)
		};

		return Fraction{ numerator / gcd, denominator / gcd };
	}

	Fraction Fraction::operator/(const Fraction& rhs) const noexcept {
		const int numerator{ getNumerator() * rhs.getDenominator() };
		const int denominator{ getDenominator() * rhs.getNumerator() };

		const auto gcd{
			utils::getGreatestCommonDenominator(numerator, denominator)
		};

		return Fraction{ numerator / gcd, denominator / gcd };
	}

	std::ostream& operator<<(std::ostream& os, const Fraction& fraction) noexcept {
		os << fraction.getStrView();

		return os;
	}

	std::istream& operator>>(std::istream& is, Fraction& fraction) noexcept {
		std::string fractionInput{};
		std::getline(std::cin >> std::ws, fractionInput);

		try {
			fraction = std::move(Fraction{ fractionInput });
		}
		catch (const std::invalid_argument&) {
			is.setstate(std::ios::failbit);
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