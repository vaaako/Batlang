#pragma once

#include <cstddef>
#include <string>

class Position {
	public:
		Position(size_t index, size_t line, size_t col, std::string filename, std::string text);

		void advance(char cc);
		// Position* advance(char cc);
		// Position copy();

		inline size_t get_index() const {
			return index;
		}

		inline size_t get_line() const {
			return line;
		}

		inline size_t get_col() const {
			return col;
		}

		inline std::string get_filename() const {
			return filename;
		}
	private:
		size_t index;
		size_t line;
		size_t col;
		std::string filename;
		std::string text;
};