#pragma once

#include "position.hpp"
#include <string>

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
};
