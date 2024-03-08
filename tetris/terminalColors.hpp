#ifndef _TETRIS_TERMINAL_COLORS_HPP
#define _TETRIS_TERMINAL_COLORS_HPP

#include<unordered_map>
#include<string_view>

using namespace std::string_view_literals;

namespace termColors {
	enum class TerminalBgColors {
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
	};

	enum class TerminalFgColors {
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
	};

	// Foreground colors / the color of symbols printed to the terminal
	const inline std::unordered_map<TerminalFgColors, std::string_view> terminalFgColors{
		{ TerminalFgColors::lightBlue, "\033[38;5;14m"sv  },
		{ TerminalFgColors::darkBlue , "\033[38;5;21m"sv  },
		{ TerminalFgColors::orange   , "\033[38;5;208m"sv },
		{ TerminalFgColors::yellow   , "\033[38;5;226m"sv },
		{ TerminalFgColors::green    , "\033[38;5;46m"sv  },
		{ TerminalFgColors::red      , "\033[38;5;160m"sv },
		{ TerminalFgColors::magenta  , "\033[38;5;129m"sv },
		{ TerminalFgColors::black    , "\033[38;5;0m"sv   },
		{ TerminalFgColors::white    , "\033[38;5;255m"sv },
		{ TerminalFgColors::grey     , "\033[38;5;249m"sv },
	};

	// Background colors
	const inline std::unordered_map<TerminalBgColors, std::string_view> terminalBgColors{
		{ TerminalBgColors::lightBlue, "\033[48;5;14m"sv  },
		{ TerminalBgColors::darkBlue , "\033[48;5;21m"sv  },
		{ TerminalBgColors::orange   , "\033[48;5;208m"sv },
		{ TerminalBgColors::yellow   , "\033[48;5;226m"sv },
		{ TerminalBgColors::green    , "\033[48;5;46m"sv  },
		{ TerminalBgColors::red      , "\033[48;5;160m"sv },
		{ TerminalBgColors::magenta  , "\033[48;5;129m"sv },
		{ TerminalBgColors::black    , "\033[48;5;0m"sv   },
		{ TerminalBgColors::white    , "\033[48;5;255m"sv },
		{ TerminalBgColors::grey     , "\033[48;5;249m"sv },
	};
}
#endif