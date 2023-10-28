#include "../headers/position.hpp"

Position::Position(size_t index, size_t line, size_t col, std::string filename, std::string text) : index(index), line(line), col(col), filename(filename), text(text) {

}

void Position::advance(char cc) {
	index++;
	col++;

	if(cc == '\n') {
		line++;
		col = 0;
	}
}

// Position Position::copy() {
// 	return *this;
// }


size_t Position::get_index() const {
	return index;
}

size_t Position::get_line() const {
	return line;
}

size_t Position::get_col() const {
	return col;
}

std::string Position::get_filename() const {
	return filename;
}