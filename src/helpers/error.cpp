#include "../headers/error.hpp"

/*
	TODO: Better error messages
	- Add "^" showing where the error occurred (need pos and pos_end)

*/
Error::Error(const ErrorType error_type, const std::string detail, const Position& pos) : detail(detail), pos(pos) {
	auto it = error_hash.find(error_type);
	name = (it == error_hash.end()) ? "Error" : it->second;
}

Error::Error(const ErrorType error_type, const std::string detail, const Position& pos, const Context& context) : detail(detail), pos(pos), context(context) {
	auto it = error_hash.find(error_type);
	name = (it == error_hash.end()) ? "Error" : it->second;
}




/* Private */
