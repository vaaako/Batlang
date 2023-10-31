#include "../headers/position.hpp"

Position::Position(size_t index, size_t line, size_t col, std::string filename, std::string text) : index(index), line(line), col(col), filename(filename), text(text) {

}

void Position::advance(char cc) {
	index++;
	col++;

	// Next line
	if(cc == '\n') {
		line++;
		col = 0;
	}
}

