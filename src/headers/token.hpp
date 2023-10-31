#pragma once

#include "position.hpp"

#include <string>
#include <optional>

enum class TokenType {
	UNKNOWN,
	// UNDEFINED,
	INT,
	FLOAT,

	PLUS,
	MINUS,
	MUL,
	DIV,
	LPARENT,
	RPARENT,
	TEOF // End of file (TEOF because EOF is a C++ macro)
};

class Token {
	public:
		// Token(TokenType type, std::string value);
		Token(TokenType type, std::string value, Position pos);

		std::string as_string();
		static TokenType from_char(char c);

		TokenType get_type() const;
		std::string get_value() const;
		Position get_pos();

	private:
		TokenType type;
		std::string value;

		Position pos;
		// std::optional<Position> pos_end;

		std::string get_token_string(TokenType type);
};