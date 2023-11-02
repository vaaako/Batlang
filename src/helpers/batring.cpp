#include "../headers/batring.hpp"

#include <iostream>

/* Helpers start */
std::unordered_map<std::string, std::string> color_hash = {
	{ "reset",    "\033[0m"  },
	{ "red",      "\033[31m" },
	{ "bold_red", "\033[1;31m" },
	{ "green",    "\033[32m" },
	{ "yellow",   "\033[33m" },
	{ "blue",     "\033[34m" },
	{ "gray",     "\033[90m" },
	{ "white",    "\033[37m" }
};

std::string Batring::colorize(std::string text, std::string color)  {
	return color_hash.at(color) + text + color_hash.at("reset");
}

std::string fix_float(const double value) {
	std::stringstream ss;
	ss << std::fixed << value;
	std::string result = ss.str();

	// Remove trailing zeros
	while(!result.empty() && (result.back() == '0' || result.back() == '.')) {
		result.pop_back();
	}
	return result;
}
/* Helpers end */




std::string Batring::num(const double value) {
	// Is int, print as Integer (1.0 => 1)
	if(value == (int)(value)) return std::to_string((int)value);
		
	// Fix decimal places
	return fix_float(value);
}

void Batring::result(const std::string value) {
	std::cout << colorize(value, "yellow");
}

void Batring::error(Error error) {
	Position pos = error.get_pos();
	std::cout << colorize(error.get_name() + ": ", "bold_red")
			+ colorize(error.get_detail(), "green")
			+ colorize("\nFile: ", "gray")
			+ colorize(pos.get_filename(), "yellow")
			+ colorize(" at index position ", "white")
			+ colorize(std::to_string(pos.get_index()), "blue")
			+ ", line "
			+ colorize(std::to_string(pos.get_line() + 1), "blue")
	<< std::endl; // It won't work without this
}

