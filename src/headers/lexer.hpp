#pragma once

// #include "result.hpp"
#include "token.hpp"
#include "error.hpp"
#include "position.hpp"

#include <optional>
#include <string>
#include <vector>

struct LexerResult {
	std::vector<Token> value;
	std::optional<Error> error;

	LexerResult(const std::vector<Token> value) : value(value) {}
	LexerResult(const Error error) : error(error) {}

	inline bool has_error() const {
		return error.has_value();
	}

	inline Error get_error() const {
		return error.value();
	}

	inline std::vector<Token> get_value() const {
		return value;
	}
};

class Lexer {
	public:
		Lexer(const std::string filename, const std::string text);
		LexerResult make_tokens();
	private:
		std::string text;
		Position pos;
		char cc = -1; // Current character
		
		Token make_num();

		// Go to next character
		void advance();

		char pop_text() {
			char c = text.at(0);
			text.erase(text.begin());
			return c;
		}

};