#pragma once

#include "position.hpp"
#include <string>

enum ErrorType {
	IllegalCharError,
	InvalidSyntaxError
};

class Error {
	public:
		// Error(Position pos_start, Position pos_end, std::string name, std::string details);
		Error(ErrorType error_type, Position pos_start, std::string details);
		std::string as_string();

	private:
		Position pos_start;
		// Position pos_end;
		std::string name;
		std::string details;
};

// class IllegalCharError : public Error {
// 	public:
// 		IllegalCharError(Position pos_start, std::string details);
// };

