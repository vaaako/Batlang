#pragma once

#include <string>

class Error {
	public:
		Error(std::string name, std::string details);

		std::string as_string();

	private:
		std::string name;
		std::string details;
};

class IllegalCharError : public Error {
	public:
		IllegalCharError(std::string details);
};