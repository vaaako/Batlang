#include "headers/error.h"

ErrorParser::ErrorParser() {}

void ErrorParser::throw_error(const std::string& err_message, std::string value) {
	std::string formated_value = " ";
	if(value.length() > 0)
		formated_value = " '" + value + "'";

	std::cerr << err_message << formated_value << std::endl;
	exit(EXIT_FAILURE);
}