#pragma once

#include "position.hpp"
#include <string>

class Error {
	public:
		Error(Position pos_start, Position pos_end, std::string name, std::string details);
		std::string as_string();

	private:
		Position pos_start;
		Position pos_end;
		std::string name;
		std::string details;
};

class IllegalCharError : public Error {
	public:
		IllegalCharError(Position pos_start, Position pos_end, std::string details);
};