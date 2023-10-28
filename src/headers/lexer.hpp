#pragma once

#include "token.hpp"
#include "error.hpp"
#include "position.hpp"

#include <optional>
#include <string>
#include <vector>

class Lexer {
	public:
		Lexer(std::string filename, std::string text);
		std::pair<std::vector<Token>, std::optional<Error>> make_tokens();
	private:
		std::string filename;
		std::string text;

		Position pos;
		char cc = -1; // Current character
		
		Token make_num();

		// Go to next character
		void advance();

};