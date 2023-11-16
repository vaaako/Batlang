#include "../headers/token.hpp"

Token::Token(const TokenType type, const Position& pos) : type(type), pos(pos) {}
Token::Token(const TokenType type, const Position& pos, const double value) : type(type), pos(pos), value(std::to_string(value)) {}
Token::Token(const TokenType type, const Position& pos, const std::string value) : type(type), pos(pos), value(value) {}

TokenType Token::from_char(const char c) {
	auto it = char_type_hash.find(c);
	return (it == char_type_hash.end()) ? TokenType::UNKNOWN : it->second;
}




/* PRIVATE */
