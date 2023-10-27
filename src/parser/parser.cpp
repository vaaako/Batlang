#include "../headers/parser.hpp"
#include <iostream>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {}

void Parser::advance() {
	if(++token_index < tokens.size())
		cur_token = tokens[token_index];
}

Node* Parser::parse() {
	return expr();
}

Node* Parser::factor() {
	Token token = cur_token;
	if(cur_token.get_type() == TokenType::INT || cur_token.get_type() == TokenType::FLOAT) {
		advance();
	}
	return new Node(token);
}


// BinOpNode
Node* Parser::term() {
	Node* left = factor();
	
	// Current token is mul or div
	while(cur_token.get_type() == TokenType::MUL || cur_token.get_type() == TokenType::DIV) {
		Token opToken = cur_token; // Grab token
		advance(); // Advance to get token from the right
		Node* right = factor();
		left = new Node(opToken, left, right);
	}

	return left;
}

// BinOpNode
Node* Parser::expr() {
	Node* left = term();
	
	while(cur_token.get_type() == TokenType::PLUS || cur_token.get_type() == TokenType::MINUS) {
		Token opToken = cur_token;
		advance();
		Node* right = term();
		left = new Node(opToken, left, right);
	}

	return left;
}
