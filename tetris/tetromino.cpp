#include"tetromino.hpp"
#include"utils.hpp"

#include<iostream>
#include<algorithm>
#include<unordered_set>
#include<utility>

namespace tetromino {
	// -------------------------------------
	// Points class definition
	// -------------------------------------
	// public
	Points::Points(std::vector<std::vector<char>>&& pointsMatrix, TerminalBgColor&& pointsColor)
		: m_pointsMatrix(std::move(pointsMatrix))
		, m_pointsColor(std::exchange(pointsColor, TerminalBgColor::Default))
	{
		rotate0Deg();
	}

	Points::Points(const Points& points)
		: m_pointsMatrix(points.m_pointsMatrix)
		, m_pointsColor(points.m_pointsColor)
		, m_currentRotation(points.m_currentRotation)
		, m_offsetPoint(points.m_offsetPoint)
	{
		rotate();
	}

	Points::Points(Points&& points) noexcept
		: m_pointsMatrix(std::move(points.m_pointsMatrix))
		, m_pointsColor(std::exchange(points.m_pointsColor, TerminalBgColor::Default))
		, m_currentRotation(std::exchange(points.m_currentRotation, minRotations))
		, m_offsetPoint(std::move(points.m_offsetPoint))
	{
		rotate();
	}

	Points& Points::operator=(const Points& points) noexcept {
		m_pointsMatrix = points.m_pointsMatrix;
		m_pointsColor = points.m_pointsColor;
		m_currentRotation = points.m_currentRotation;
		m_offsetPoint = points.m_offsetPoint;

		rotate();

		return *this;
	}

	Points& Points::operator=(Points&& points) noexcept {
		m_pointsMatrix = std::move(points.m_pointsMatrix);
		m_pointsColor = std::exchange(points.m_pointsColor, TerminalBgColor::Default);
		m_currentRotation = std::exchange(points.m_currentRotation, minRotations);
		m_offsetPoint = std::move(points.m_offsetPoint);

		rotate();

		return *this;
	}

	TerminalBgColor Points::getPointsColor() const noexcept {
		return m_pointsColor;
	}

	Points::ConstIterator Points::begin() const noexcept {
		return m_points.begin();
	}

	Points::ConstIterator Points::end() const noexcept {
		return m_points.end();
	}

	Points::Iterator Points::begin() noexcept {
		return m_points.begin();
	}

	Points::Iterator Points::end() noexcept {
		return m_points.end();
	}

	void Points::offsetAllPointsBy(const PointType& offsetPoint) noexcept {
		m_offsetPoint = offsetPoint;

		for (auto& point : m_points) {
			point.first += offsetPoint.first;
			point.second += offsetPoint.second;
		}
	}

	bool Points::doesPointExist(const PointType& findPoint) const noexcept {
		return std::find(m_points.begin(), m_points.end(), findPoint) != m_points.end();
	}

	void Points::rotateLeft() noexcept {
		--m_currentRotation;
		
		if (m_currentRotation < minRotations) {
			m_currentRotation = maxRotations;
		}

		rotate();
	}
	
	void Points::rotateRight() noexcept {
		++m_currentRotation;

		if (m_currentRotation > maxRotations) {
			m_currentRotation = minRotations;
		}

		rotate();
	}

	void Points::moveOffsetUp() noexcept {
		if (m_offsetPoint.first == 0) {
			return;
		}
		--m_offsetPoint.first;
	}

	void Points::moveOffsetDown() noexcept {
		++m_offsetPoint.first;
	}

	void Points::moveOffsetLeft() noexcept {
		if (m_offsetPoint.second == 0) {
			return;
		}

		--m_offsetPoint.second;
	}

	void Points::moveOffsetRight() noexcept {
		++m_offsetPoint.second;
	}

	// private

	void Points::rotate() noexcept {
		switch (m_currentRotation) {
		case 0:
			rotate0Deg();
			break;
		case 1:
			rotate90Deg();
			break;
		case 2:
			rotate180Deg();
			break;
		case 3:
			rotate270Deg();
			break;
		}
	}

	void Points::rotate0Deg() noexcept {
		m_points.clear();

		for (std::size_t i = 0; i < m_pointsMatrix.size(); ++i) {
			for (std::size_t ii = 0; ii < m_pointsMatrix[i].size(); ++ii) {
				if (m_pointsMatrix[i][ii]) {
					const FirstSecondType first{ static_cast<FirstSecondType>(i) + m_offsetPoint.first };
					const FirstSecondType second{ static_cast<FirstSecondType>(ii) + m_offsetPoint.second };

					m_points.push_back({first, second});
				}
			}
		}
	}

	void Points::rotate90Deg() noexcept {
		m_points.clear();

		for (std::size_t ii = 0; ii < m_pointsMatrix[0].size(); ++ii) {
			for (std::ptrdiff_t i = m_pointsMatrix.size() - 1; i >= 0; --i) {
				if (m_pointsMatrix[i][ii]) {
					const FirstSecondType first{ static_cast<FirstSecondType>(ii) + m_offsetPoint.first };
					const FirstSecondType second{ static_cast<FirstSecondType>(m_pointsMatrix.size() - 1 - i) + m_offsetPoint.second };

					m_points.push_back({ first, second });
				}
			}
		}
	}

	void Points::rotate180Deg() noexcept {
		m_points.clear();

		for (std::ptrdiff_t i = m_pointsMatrix.size() - 1; i >= 0; --i) {
			for (std::ptrdiff_t ii = m_pointsMatrix[i].size() - 1; ii >= 0; --ii) {
				if (m_pointsMatrix[i][ii]) {
					const FirstSecondType first{ static_cast<FirstSecondType>(m_pointsMatrix.size() - 1 - i) + m_offsetPoint.first };
					const FirstSecondType second{ static_cast<FirstSecondType>(m_pointsMatrix[0].size() - 1 - ii) + m_offsetPoint.second };

					m_points.push_back({ first, second });
				}
			}
		}
	}

	void Points::rotate270Deg() noexcept {
		m_points.clear();

		for (std::ptrdiff_t ii = m_pointsMatrix[0].size() - 1; ii >= 0; --ii) {
			for (std::ptrdiff_t i = m_pointsMatrix.size() - 1; i >= 0; --i) {
				if (m_pointsMatrix[i][ii]) {
					const FirstSecondType first{ static_cast<FirstSecondType>(m_pointsMatrix[0].size() - 1 - ii) + m_offsetPoint.first };
					const FirstSecondType second{ static_cast<FirstSecondType>(m_pointsMatrix.size() - 1 - i) + m_offsetPoint.second };

					m_points.push_back({ first, second });
				}
			}
		}
	}
}
