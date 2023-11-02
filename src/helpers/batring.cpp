#include "../headers/batring.hpp"

std::string Batring::num(const double value) {
	// Is int, print as Integer (1.0 => 1)
	if(value == (int)(value)) return std::to_string((int)value);
		
	// Fix decimal places
	return Batring::fix_float(value);
}

std::string Batring::result(const std::string value) {
	return "\033[33m" + value + "\033[0m";
}