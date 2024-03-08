#include"tetromino.hpp"
#include"utils.hpp"
#include<iostream>

namespace tetromino {
	Tetromino::Tetromino(std::vector<std::vector<terminalColors::BackgroundColors>>&& shape)
		: m_shape(shape)
	{}

	void Tetromino::rotate(const bool rotateRight) noexcept {
		const std::size_t endIndex{ m_shape.size() - 1 };

		for (std::size_t i = 0; i < endIndex - i; i++) {
			for (std::size_t ii = i; ii < endIndex; ii++) {
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

	std::ostream& operator<<(std::ostream& os, const tetromino::Tetromino& tetromino) {
		for (const auto& bgColorRows : tetromino.m_shape) {
			for (const auto& bgColor : bgColorRows) {
				utils::colorSpaceInTerminal(bgColor);
			}
			os << '\n';
		}

		return os;
	}
}
