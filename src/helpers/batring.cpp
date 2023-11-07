#include "../headers/batring.hpp"

#include <algorithm>
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

std::string Batring::colorize(const std::string& text, const std::string color)  {
	return color_hash.at(color) + text + color_hash.at("reset");
}

std::string fix_float(const double& value) {
	std::stringstream ss;
	ss << std::fixed << value;
	std::string result = ss.str();

	// Remove trailing zeros
	while(!result.empty() && (result.back() == '0' || result.back() == '.')) {
		result.pop_back();
	}
	return result;
}

std::string generate_traceback(Context context) {
	std::string result = "";
	// const Position pos = context.get_pos();
	result += Batring::colorize("\nIn: ", "gray")
			+ Batring::colorize(context.get_name(), "yellow");

	// If has parent generate traceback for all parents
	if(context.has_parent()) result += generate_traceback(context.get_parent());
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


/**
 * To improve context message I need to improve the recursive, instead of making recursive with context itself
 * I need to make recusive with Error object 
 * 
 * Something like that:

Position pos = error.get_pos();
Context context = error.get_context();

while(context) {
	result += *message*;
	pos = context.get_pos();
}

return result
*/

void Batring::error(const Error& error) {
	std::string result;
	const Position pos = error.get_pos();

	// Erro name display
	result += colorize(error.get_name() + ": ", "bold_red")
			+ colorize(error.get_detail(), "green");

	// Error traceback display
	if(error.has_context()) result += generate_traceback(error.get_context());
	result += Batring::colorize("\nFile: ", "gray")
			+ Batring::colorize(pos.get_filename(), "yellow")
			+ Batring::colorize(" at index position ", "white")
			+ Batring::colorize(std::to_string(pos.get_index()), "blue")
			+ ", line "
			+ Batring::colorize(std::to_string(pos.get_line() + 1), "blue");

	std::cout << result << std::endl; // It won't work without std::endl
}


