#pragma once

#include "position.hpp"
#include <string>
#include <unordered_map>

enum ErrorType {
	IllegalCharError,
	InvalidSyntaxError,
	RuntimeError
};

class Error {
	public:
		// Error(Position pos, Position pos_end, std::string name, std::string details);
		Error(ErrorType error_type, Position pos, std::string details);
		inline std::string as_string() const {
			return colorize(name + ": ", "bold_red")
					+ colorize(details, "green")
					+ colorize("\nFile: ", "gray")
					+ colorize(pos.get_filename(), "yellow")
					+ colorize(" at index position ", "white")
					+ colorize(std::to_string(pos.get_index()), "blue")
					+ ", line "
					+ colorize(std::to_string(pos.get_line() + 1), "blue");
		}

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

		std::unordered_map<ErrorType, std::string> error_hash = {
			{ IllegalCharError,   "Illegal Character"  },
			{ InvalidSyntaxError, "Invalid Syntax" },
			{ RuntimeError,       "Runtime Error" },
		};

		inline std::string colorize(std::string text, std::string color) const {
			return color_hash.at(color) + text + color_hash.at("reset");
		}
};
