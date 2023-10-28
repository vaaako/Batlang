#pragma once

#include <cstddef>
#include <string>

class Position {
	public:
		Position(size_t index, size_t line, size_t col, std::string filename, std::string text);

		void advance(char cc);
		// Position* advance(char cc);
		// Position copy();

		size_t get_index() const;
		size_t get_line() const;
		size_t get_col() const;
		std::string get_filename() const;
	private:
		size_t index;
		size_t line;
		size_t col;
		std::string filename;
		std::string text;
};