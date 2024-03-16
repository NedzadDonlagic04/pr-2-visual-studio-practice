#include"tetromino.hpp"
#include"utils.hpp"
#include<iostream>
#include<algorithm>

namespace tetromino {
	// -------------------------------------
	// Tetromino class implementation
	// -------------------------------------

	// public
	Tetromino::Tetromino(const std::vector<std::vector<terminalColors::BackgroundColors>>& shape)
		: m_shape(shape)
	{}

	Tetromino::Tetromino(std::vector<std::vector<terminalColors::BackgroundColors>>&& shape)
		: m_shape(shape)
	{}

	Tetromino::Tetromino(std::initializer_list<std::initializer_list<terminalColors::BackgroundColors>>&& shape)
		: m_shape(shape.begin(), shape.end())
	{}

	std::size_t Tetromino::getShapeHeight() const noexcept {
		for (std::ptrdiff_t i = m_shape.size() - 1; i >= 0; --i) {
			const bool isEntireRowDefaultColor{ std::all_of(m_shape[i].begin(), m_shape[i].end(),
				[](const auto color) {
					return color == TerminalBgColor::Default;
				}
			) };

			if (!isEntireRowDefaultColor) {
				return i + 1;
			}
		}

		return m_shape.size();
	}

	std::size_t Tetromino::getShapeWidth() const noexcept {
		return m_shape[0].size();
	}

	void Tetromino::rotateLeft() noexcept {
		rotate();
	}

	void Tetromino::rotateRight() noexcept {
		rotate(true);
	}
	
	terminalColors::BackgroundColors Tetromino::operator()(const std::size_t rowsIndex, const std::size_t colsIndex) const noexcept {
		return m_shape[rowsIndex][colsIndex];
	}

	// private

	void Tetromino::rotate(const bool rotateRight) noexcept {
		const std::size_t endIndex{ m_shape.size() - 1 };
			
		for (std::size_t i = 0; i < endIndex - i; ++i) {
			for (std::size_t ii = i; ii < endIndex - i; ++ii) {
				if (rotateRight) {
					std::swap(m_shape[i][ii], m_shape[ii][endIndex - i]);
					std::swap(m_shape[i][ii], m_shape[endIndex - i][endIndex - ii]);
					std::swap(m_shape[i][ii], m_shape[endIndex - ii][i]);
				}
				else {
					std::swap(m_shape[i][ii], m_shape[endIndex - ii][i]);
					std::swap(m_shape[i][ii], m_shape[endIndex - i][endIndex - ii]);
					std::swap(m_shape[i][ii], m_shape[ii][endIndex - i]);
				}
			}
		}
	}
}
