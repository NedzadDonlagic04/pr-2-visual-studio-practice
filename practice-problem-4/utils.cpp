#include"utils.hpp"

namespace utils {
	std::vector<std::string_view> splitStrView(const std::string_view str, const std::string_view delimiter) {
		std::vector<std::string_view> splitVector {};
		std::size_t start{ 0 }, end{};

		while ((end = str.find(delimiter, start)) != std::string_view::npos) {
			splitVector.push_back(str.substr(start, end - start));
			start = end + 1;
		}

		splitVector.push_back(str.substr(start, str.size() - start));

		return splitVector;
	}
}