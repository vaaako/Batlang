#pragma once

// #include "result.hpp"
#include "token.hpp"
#include "error.hpp"
#include "position.hpp"

#include <array>
#include <cctype>
#include <optional>
#include <string>
#include <vector>

struct LexerResult {
	std::vector<Token> value;
	std::optional<Error> error;

	LexerResult(const std::vector<Token> value) : value(value) {}
	LexerResult(const Error& error) : error(error) {}

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
		Lexer(const std::string& filename, const std::string& text);
		LexerResult make_tokens();

	private:
		std::string text;
		Position pos;
		char cc = -1; // Current character

		const std::array<std::string, 2> keywords = {
			"let"
		};


		
		bool keywordExists(const std::string& target) const;

		Token make_identifier();
		Token make_num();

		// Go to next character
		inline void advance() {
			pos.advance(cc);
			cc = (text.length() != 0) ? pop_text() : -1;
		}

		inline bool is_identifier(const char cc) {
			return std::isalnum(cc) || cc == '_' || cc == '/';
		}

		inline char pop_text() {
			char c = text.at(0);
			text.erase(text.begin());
			return c;
		}
};