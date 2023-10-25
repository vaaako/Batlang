#pragma once

#include <cstddef>
#include <string>

enum TokenType {
	UNKNOWN,
	UNDEFINED,
	INT,
	FLOAT,

	PLUS,
	MINUS,
	MUL,
	DIV,
	LPARENT,
	RPARENT,
};

class Token {
	public:
		Token(TokenType type, std::string value);

		std::string as_string();
		static TokenType from_char(char c);

		// TokenType get_type();
		// TokenValue get_value();
	private:
		TokenType type;
		std::string value;

		std::string get_token_string(TokenType type);
};