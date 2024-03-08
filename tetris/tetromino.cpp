#include"tetromino.hpp"
#include"utils.hpp"
#include<iostream>

namespace tetromino {
	// -------------------------------------
	// Tetromino class implementation
	// -------------------------------------
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
		return m_shape.size();
	}

	std::size_t Tetromino::getShapeWidth() const noexcept {
		return m_shape[0].size();
	}

	void Tetromino::rotate(const bool rotateRight) noexcept {
		const std::size_t endIndex{ m_shape.size() - 1 };

		for (std::size_t i = 0; i < endIndex - i; i++) {
			for (std::size_t ii = i; ii < endIndex - i; ii++) {
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

	std::ostream& operator<<(std::ostream& os, const Tetromino& tetromino) {
		for (const auto& bgColorRows : tetromino.m_shape) {
			for (const auto& bgColor : bgColorRows) {
				utils::colorSpaceInTerminal(bgColor);
			}
			os << '\n';
		}

		return os;
	}

	// -------------------------------------
	// functions and constants declaration / definitions
	// -------------------------------------

	void printAllRotationsOfATetromino(Tetromino& tetromino) {
		for (int i = 0; i < 4; i++) {
			std::cout << tetromino << '\n';
			tetromino.rotate();
		}

		std::cout << tetromino << '\n';
	}
}
