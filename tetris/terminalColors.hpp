#ifndef _TETRIS_TERMINAL_COLORS_HPP
#define _TETRIS_TERMINAL_COLORS_HPP

#include<unordered_map>
#include<string_view>

using namespace std::string_view_literals;

/*
	Source for the color codes
	https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#256-colors
*/

namespace terminalColors {
	enum class BackgroundColors {
		lightBlue,
		darkBlue,
		orange,
		yellow,
		green,
		red,
		magenta,
		black,
		white,
		grey,
		// "Default" has the first letter capitalized due to
		// "default" being a keyword
		Default,
	};

	enum class ForegroundColors {
		lightBlue,
		darkBlue,
		orange,
		yellow,
		green,
		red,
		magenta,
		black,
		white,
		grey,
		// "Default" has the first letter capitalized due to
		// "default" being a keyword
		Default,
	};

	// Background colors
	const inline std::unordered_map<BackgroundColors, std::string_view> backgroundColors{
		{ BackgroundColors::lightBlue	, "\033[48;5;14m"sv  },
		{ BackgroundColors::darkBlue	, "\033[48;5;21m"sv  },
		{ BackgroundColors::orange		, "\033[48;5;208m"sv },
		{ BackgroundColors::yellow		, "\033[48;5;226m"sv },
		{ BackgroundColors::green		, "\033[48;5;46m"sv  },
		{ BackgroundColors::red			, "\033[48;5;160m"sv },
		{ BackgroundColors::magenta		, "\033[48;5;129m"sv },
		{ BackgroundColors::black		, "\033[48;5;0m"sv   },
		{ BackgroundColors::white		, "\033[48;5;255m"sv },
		{ BackgroundColors::grey		, "\033[48;5;249m"sv },
		{ BackgroundColors::Default     , "\033[49m"sv       },
	};

	// Foreground colors / the color of symbols printed to the terminal
	const inline std::unordered_map<ForegroundColors, std::string_view> foregroundColors{
		{ ForegroundColors::lightBlue	, "\033[38;5;14m"sv  },
		{ ForegroundColors::darkBlue	, "\033[38;5;21m"sv  },
		{ ForegroundColors::orange		, "\033[38;5;208m"sv },
		{ ForegroundColors::yellow		, "\033[38;5;226m"sv },
		{ ForegroundColors::green		, "\033[38;5;46m"sv  },
		{ ForegroundColors::red			, "\033[38;5;160m"sv },
		{ ForegroundColors::magenta		, "\033[38;5;129m"sv },
		{ ForegroundColors::black		, "\033[38;5;0m"sv   },
		{ ForegroundColors::white		, "\033[38;5;255m"sv },
		{ ForegroundColors::grey		, "\033[38;5;249m"sv },
		{ ForegroundColors::Default     , "\033[39m"sv       },
	};
}
#endif