#include"memoryLine.hpp"
#include"utils.hpp"

namespace memory {
	// ----------------------------------------------
	// MemoryLine declaration
	// ----------------------------------------------
	// public
	bool MemoryLine::isConvertableTo(const MemoryLine& memoryLine) const {
		if (size() != memoryLine.size()) {
			return false;
		}

		for (std::size_t i = 0; i < size(); ++i) {
			if (!at(i).isConvertableTo(memoryLine.at(i))) {
				return false;
			}
		}

		return true;
	}

	unsigned int MemoryLine::getTimeInNsToConvertTo(const MemoryLine& memoryLine) const noexcept {
		unsigned int totalConversionTime{ 0 };

		for (std::size_t i = 0; i < size(); ++i) {
			totalConversionTime += at(i).getTimeInNsToConvertTo(memoryLine.at(i));
		}

		return totalConversionTime;
	}

	MemoryLine& MemoryLine::operator=(const MemoryLine& memoryLine) {
		m_memoryBlocks = memoryLine.getMemoryBlocks();

		return *this;
	}

	const MemoryBlock MemoryLine::at(const std::size_t index) const {
		return m_memoryBlocks.at(index);
	}

	std::size_t MemoryLine::size() const noexcept {
		return m_memoryBlocks.size();
	}

	// private
	MemoryLine::MemoryLine(std::vector<MemoryBlock> memoryBlocks) noexcept {
		m_memoryBlocks = std::move(memoryBlocks);
	}

	std::vector<MemoryBlock>& MemoryLine::getMemoryBlocks() noexcept {
		return m_memoryBlocks;
	}
	
	const std::vector<MemoryBlock>& MemoryLine::getMemoryBlocks() const noexcept {
		return m_memoryBlocks;
	}

	MemoryBlock& MemoryLine::operator[](const std::size_t index) {
		return m_memoryBlocks[index];
	}

	// friend function definitions
	std::ostream& operator<<(std::ostream& os, const MemoryLine& memoryLine) noexcept {
		for (std::size_t i = 0; i < memoryLine.size(); ++i) {
			os << memoryLine.at(i);
			if (i + 1 != memoryLine.size()) {
				os << MemoryLine::memoryBlocksDelimiter;
			}
		}

		return os;
	}

	std::optional<MemoryLine> createMemoryLine(
		const std::string_view memoryLineStr,
		MemoryErrorHandler& errorHandler
	) noexcept {
		const auto potentialMemoryBlocks{ 
			utils::splitStrView(memoryLineStr, MemoryLine::memoryBlocksDelimiter)
		};

		MemoryErrorHandler state {};
		std::vector<MemoryBlock> memoryLine{};
		
		for (const auto memoryBlock : potentialMemoryBlocks) {
			auto tempMemoryBlock{ createMemoryBlock(memoryBlock, state) };
			
			if (!state) {
				errorHandler = state;
				return {};
			}

			memoryLine.push_back(std::move(tempMemoryBlock.value()));
		}

		return MemoryLine(memoryLine);	
	}
}