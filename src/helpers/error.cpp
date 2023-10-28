#include "../headers/error.hpp"
#include <string>

/*
	TODO: Better error messages
	- Add "^" showing where the error occurred (need pos and pos_end)

*/
Error::Error(ErrorType error_type, Position pos, std::string details) : pos(pos), details(details) {
	switch (error_type) {
		case IllegalCharError:
			name = "Illegal Character";
			break;
		case InvalidSyntaxError:
			name = "Invalid Syntax";
			break;
		default:
			name = "Error";
	}
}

std::string Error::as_string() {
	return colorize(name + ": ", "bold_red")
			+ colorize(details, "green")
			+ colorize("\nFile: ", "gray")
			+ colorize(pos.get_filename(), "yellow")
			+ colorize(" at index position ", "white")
			+ colorize(std::to_string(pos.get_index()), "blue")
			+ ", line "
			+ colorize(std::to_string(pos.get_line() + 1), "blue");
}

/* Private */
std::string Error::colorize(std::string text, std::string color) {
	return color_hash.at(color) + text + color_hash.at("reset");
}
