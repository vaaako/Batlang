#pragma once

#include <iostream>
#include <optional>

class ErrorParser {
	public:
		ErrorParser();

		static void throw_error(const std::string& err_message, std::string value="");
};