#pragma once

#include "error.hpp"

#include <sstream>
#include <string>
#include <iomanip>


// TODO mark hash map as const later

// I used namaspace instead of a class because every method in here would be static
namespace Batring {
	std::string colorize(const std::string& text, const std::string color);

	std::string num(const double value);
	std::string num(const std::string value);

	void result(const std::string value);
	void error(const Error& error);
};