#pragma once

#include "token.h"
#include "error.h"

#include <optional>
#include <string>
#include <vector>

class Lexer {
	public:
		Lexer(std::string text);

		std::pair<std::vector<Token>, std::optional<Error>> make_tokens();
	private:
		std::string text;

		size_t pos = 0;
		char cc = -1; // Current character
		
		Token make_num();

		// Go to next character
		void advance();

};