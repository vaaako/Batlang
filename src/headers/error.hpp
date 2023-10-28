#pragma once

#include "position.hpp"
#include <string>
#include <unordered_map>

enum ErrorType {
	IllegalCharError,
	InvalidSyntaxError
};

class Error {
	public:
		// Error(Position pos, Position pos_end, std::string name, std::string details);
		Error(ErrorType error_type, Position pos, std::string details);
		std::string as_string();

	private:
		Position pos;
		std::string name;
		std::string details;

		std::unordered_map<std::string, std::string> color_hash = {
			{ "reset",    "\033[0m"  },
			{ "red",      "\033[31m" },
			{ "bold_red", "\033[1;31m" },
			{ "green",    "\033[32m" },
			{ "yellow",   "\033[33m" },
			{ "blue",     "\033[34m" },
			{ "gray",     "\033[90m" },
			{ "white",     "\033[37m" }
		};

		std::string colorize(std::string text, std::string color);

};
