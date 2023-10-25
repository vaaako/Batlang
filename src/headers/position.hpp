#pragma once

#include <cstddef>
#include <string>

class Position {
	public:
		Position(size_t index, size_t line, size_t col, std::string filename, std::string text);

		Position* advance(char cc);
		Position copy();

		size_t get_index();
		size_t get_line();
		size_t get_col();
		std::string get_filename();
	private:
		size_t index;
		size_t line;
		size_t col;
		std::string filename;
		std::string text;
};