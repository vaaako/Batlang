#include "../headers/token.hpp"

Token::Token(TokenType type, Position pos) : type(type), pos(pos) {}
Token::Token(TokenType type, Position pos, double value) : type(type), pos(pos), value(value) {}

TokenType Token::from_char(char c) {
	auto it = char_type_hash.find(c);
	return (it == char_type_hash.end()) ? TokenType::UNKNOWN : it->second;
}




/* PRIVATE */
