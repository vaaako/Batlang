#include "../headers/token.hpp"
#include <optional>

// Token::Token(TokenType type, std::string value) : type(type), value(value) {}
Token::Token(TokenType type, std::string value, Position pos) : type(type), value(value), pos(pos) {}

TokenType Token::enum_from_char(char c) {
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





/* PRIVATE */
std::string Token::get_token_string(TokenType type) const {
	switch (type) {
		// case TokenType::UNDEFINED: return "UNDEFINED";
		case TokenType::INT: return "INT";
		case TokenType::FLOAT: return "FLOAT";
		case TokenType::PLUS: return "PLUS";
		case TokenType::MINUS: return "MINUS";
		case TokenType::MUL: return "MUL";
		case TokenType::DIV: return "DIV";
		case TokenType::LPARENT: return "LPARENT";
		case TokenType::RPARENT: return "RPARENT";
		case TokenType::TEOF: return "EOF";
		default: return "Unkown";
	}
}