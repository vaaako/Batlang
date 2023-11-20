#pragma once

#include "position.hpp"
#include "batring.hpp"

#include <cctype>
#include <optional>
#include <string>
#include <unordered_map>
#include <iostream>


enum class TokenType {
	UNKNOWN,
	// UNDEFINED,

	// Number values
	INT,
	FLOAT,

	// String Values
	IDENTIFIER,
	KEYWORD,

	// No values (Char)
	PLUS,
	MINUS,
	MUL,
	DIV,
	POW,
	EQUALS,
	LPAREN,
	RPAREN,

	TEOF // End of file (TEOF because EOF is a C++ macro)
};


const std::unordered_map<char, TokenType> char_type_hash = {
	{ '+', TokenType::PLUS },
	{ '-', TokenType::MINUS },
	{ '*', TokenType::MUL },
	{ '/', TokenType::DIV },
	{ '^', TokenType::POW },
	{ '=', TokenType::EQUALS },
	{ '(', TokenType::LPAREN },
	{ ')', TokenType::RPAREN }

};

// template <typename T, typename = std::enable_if_t<std::is_enum_v<T> && std::is_same_v<T, TokenType>>>

// Change this later
class Token {
	public:
		Token(const TokenType type, const Position& pos);
		Token(const TokenType type, const Position& pos, const double value);
		Token(const TokenType type, const Position& pos, const std::string value);
		static TokenType from_char(const char c);

		inline std::string as_string() const {
			return type_hash.at(type) + ":" + value_as_string();
		}

		inline TokenType get_type() const {
			return type;
		}

		inline Position get_pos() const {
			return pos;
		}

		// Get value from "Value"
		inline std::string get_value() const {
			// return (value.has_value()) ? value.value() : value_as_string();
			return value_as_string();
		}

		inline double get_value_as_number() const {
			return std::stod(value.value());
		}
	
		inline bool has_value() const {
			return value.has_value();
		}


		// Return type (e.g. "+" if not a number) or value (e.g. "41" if a number) as string
		// This function is >debug only<
		std::string value_as_string() const {
			if(value.has_value())
				// Has value and is a number else return value
				return (type == TokenType::INT || type == TokenType::FLOAT) ? Batring::num(value.value()) : value.value();
			// Else not a number = below

			// This is the only Token (besides number and stuff) that is not a char
			if(type == TokenType::TEOF) return "EOF";

			// Reverse map
			std::unordered_map<TokenType, char> reverse_hash;
			for (const auto& pair : char_type_hash)
				reverse_hash[pair.second] = pair.first;

			// Get char from reversed hash, if not found, just return Token's value
			return std::string(1, reverse_hash.at(type));
		}


	private:
		TokenType type;
		Position pos;
		/**
		 * pos_start is optional
		 * if has pos_start as constructor paramter
		 * 	- pos_end = copy of pos_start
		 * 	- pos_end.advance()
		 * 
		 * */

		std::optional<std::string> value;
		// std::optional<Position> pos_end;

		std::unordered_map<TokenType, std::string> type_hash = {
			{ TokenType::INT,        "INT" },
			{ TokenType::FLOAT,      "FLOAT" },
			{ TokenType::IDENTIFIER, "IDENTIFIER" },
			{ TokenType::KEYWORD,    "KEYWORD" },
			{ TokenType::PLUS,       "PLUS" },
			{ TokenType::MINUS,      "MINUS" },
			{ TokenType::MUL,        "MUL" },
			{ TokenType::DIV,        "DIV" },
			{ TokenType::POW,        "POW" },
			{ TokenType::EQUALS,     "EQUALS" },
			{ TokenType::LPAREN,    "LPAREN" },
			{ TokenType::RPAREN,    "RPAREN" },
			{ TokenType::TEOF,       "EOF" }
		};
};