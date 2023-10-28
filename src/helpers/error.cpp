#include "../headers/error.hpp"
#include <string>

Error::Error(ErrorType error_type, Position pos_start, std::string details) : pos_start(pos_start), details(details) {
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
	return name + ": " + details + "\nFile: " + pos_start.get_filename() + ", line " + std::to_string(pos_start.get_line() + 1);
}




// IllegalCharError::IllegalCharError(Position pos_start, std::string details) : Error(pos_start, "Illegal Character", details) {}
// InvalidSyntaxError::InvalidSyntaxError(Position pos_start, std::string details) : Error(pos_start, "Illegal Character", details) {}
