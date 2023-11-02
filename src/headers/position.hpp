#pragma once

#include <cstddef>
#include <string>

class Position {
	public:
		Position(const size_t index, const size_t line, const size_t col, const std::string filename, const std::string text);
		void advance(const char cc);

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