#pragma once

#include "token.hpp"
#include "error.hpp"
#include "position.hpp"

#include <optional>
#include <string>
#include <vector>

// Lexer result
struct LResult {
	std::vector<Token> tokens;
	std::optional<Error> error;

	// LResult(std::vector<Token> tokens, Error error) : tokens(tokens), error(error) {}
	LResult(std::vector<Token> tokens) : tokens(tokens) {}
	LResult(Error error) : tokens({}), error(error) {}
};

class Lexer {
	public:
		Lexer(std::string filename, std::string text);
		LResult make_tokens();
	private:
		std::string text;

		Position pos;
		char cc = -1; // Current character
		
		Token make_num();

		// Go to next character
		void advance();

};