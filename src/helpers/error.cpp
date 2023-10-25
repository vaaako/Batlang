#include "../headers/error.hpp"
#include <string>

Error::Error(Position pos_start, Position pos_end, std::string name, std::string details) : pos_start(pos_start), pos_end(pos_end), name(name), details(details) {}

std::string Error::as_string() {
	return name + ": " + details + "\nFile: " + pos_start.get_filename() + ", line " + std::to_string(pos_start.get_line() + 1);
}



IllegalCharError::IllegalCharError(Position pos_start, Position pos_end, std::string details) : Error(pos_start, pos_end, "Illegal Character", details) {}
