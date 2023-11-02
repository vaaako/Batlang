#include "../headers/error.hpp"
#include <string>

/*
	TODO: Better error messages
	- Add "^" showing where the error occurred (need pos and pos_end)

*/
Error::Error(const ErrorType error_type, const Position pos, const std::string details) : pos(pos), details(details) {
	auto it = error_hash.find(error_type);
	name = (it == error_hash.end()) ? "Error" : it->second;
}



/* Private */
