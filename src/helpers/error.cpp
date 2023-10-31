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



/* Private */
