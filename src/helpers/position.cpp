#include "../headers/position.hpp"

Position::Position(const size_t index, const size_t line, const size_t col, const std::string& filename, const std::string& text) : index(index), line(line), col(col), filename(filename), text(text) {}

void Position::advance(const char cc) {
	index++;
	col++;

	// Next line
	if(cc == '\n') {
		line++;
		index = 0; // Reset index on changing line
		col = 0;
	}
}

