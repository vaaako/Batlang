#include "headers/token.h"

Token::Token(TokenType type, std::string value) : type(type), value(value) {};

std::string Token::print_token() {
	return get_token_string(type) + ":" + value;
	// return get_token_string(type);
}

TokenType Token::from_char(char c) {
	switch (c) {
		case '+': return TokenType::PLUS;
		case '-': return TokenType::MINUS;
		case '*': return TokenType::MUL;
		case '/': return TokenType::DIV;
		case '(': return TokenType::LPARENT;
		case ')': return TokenType::RPARENT;
		default: return TokenType::UNKNOWN;
	}
}


/* Private */
std::string Token::get_token_string(TokenType type) {
	return TokenTypeString[type];
}