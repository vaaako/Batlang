#include "headers/token.h"

Token::Token(TokenType type, std::string value) : type(type), value(value) {};

std::string Token::as_string() {
	return get_token_string(type) + ":" + value;
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
	switch (type) {
		case TokenType::UNDEFINED: return "UNDEFINED";
		case TokenType::INT: return "INT";
		case TokenType::FLOAT: return "FLOAT";
		case TokenType::PLUS: return "PLUS";
		case TokenType::MINUS: return "MINUS";
		case TokenType::MUL: return "MUL";
		case TokenType::DIV: return "DIV";
		case TokenType::LPARENT: return "LPARENT";
		case TokenType::RPARENT: return "RPARENT";
		default: return "Unkown";
	}
}