#pragma once

#include "position.hpp"
#include "batring.hpp"

#include <optional>
#include <string>
#include <unordered_map>
#include <iostream>


enum class TokenType {
	UNKNOWN,
	// UNDEFINED,
	INT,
	FLOAT,

	PLUS,
	MINUS,
	MUL,
	DIV,
	POW,
	LPARENT,
	RPARENT,
	TEOF // End of file (TEOF because EOF is a C++ macro)
};


const std::unordered_map<char, TokenType> char_type_hash = {
	{ '+', TokenType::PLUS },
	{ '-', TokenType::MINUS },
	{ '*', TokenType::MUL },
	{ '/', TokenType::DIV },
	{ '^', TokenType::POW },
	{ '(', TokenType::LPARENT },
	{ ')', TokenType::RPARENT }

};

class Token {
	public:
		Token(const TokenType type, const Position& pos);
		Token(const TokenType type, const Position& pos, const double value);
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
		inline double get_value() const {
			return value.value();
		}
	
		inline bool has_value() const {
			return value.has_value();
		}


		// Return type (e.g. "+" if not a number) or value (e.g. "41" if a number) as string
		std::string value_as_string() const {
			// Is a number
			if(value.has_value()) return Batring::num(value.value());
			// Else not a number -> below

			// This is the only Token (besides number and stuff) that is not a char
			if(type == TokenType::TEOF) return "EOF";

			// Revere map
			std::unordered_map<TokenType, char> reverse_hash;
			for (const auto& pair : char_type_hash)
				reverse_hash[pair.second] = pair.first;

			// Get char from reversed hash
			// std::cout << "Type: " << std::to_string(type) << std::endl;
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

		std::optional<double> value;
		// std::optional<Position> pos_end;

		std::unordered_map<TokenType, std::string> type_hash = {
			{ TokenType::INT,     "INT" },
			{ TokenType::FLOAT,   "FLOAT" },
			{ TokenType::PLUS,    "PLUS" },
			{ TokenType::MINUS,   "MINUS" },
			{ TokenType::MUL,     "MUL" },
			{ TokenType::DIV,     "DIV" },
			{ TokenType::POW,     "POW" },
			{ TokenType::LPARENT, "LPARENT" },
			{ TokenType::RPARENT, "RPARENT" },
			{ TokenType::TEOF,    "EOF" }
		};
};