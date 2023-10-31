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
		static TokenType enum_from_char(char c);



		inline std::string as_string() const {
			return get_token_string(type) + ":" + value;
		}

		inline TokenType get_type() const {
			return type;
		}

		inline std::string get_value() const {
			return value;
		}

		inline Position get_pos() const {
			return pos;
		}

	private:
		TokenType type;
		std::string value;

		Position pos;
		// std::optional<Position> pos_end;

		std::string get_token_string(TokenType type) const;
};