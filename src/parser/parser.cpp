#include "../headers/parser.hpp"
#include "../headers/error.hpp"

#include <iostream>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {}

void Parser::advance() {
	if(++token_index < tokens.size())
		cur_token = tokens[token_index];
}

Node* Parser::parse() {
	return expr(); // MUL and DIV priority
}

Node* Parser::factor() {
	Token token = cur_token;
	if(cur_token.get_type() == TokenType::INT || cur_token.get_type() == TokenType::FLOAT) {
		advance();
	} else { // Don't start with number
		std::cerr << "Not" << std::endl;
	}
	return new Node(token);
}


// BinOpNode
Node* Parser::term() {
	return bind_op(TokenType::MUL, TokenType::DIV, std::bind(&Parser::factor, this));
}

// BinOpNode
Node* Parser::expr() {
	return bind_op(TokenType::PLUS, TokenType::MINUS, std::bind(&Parser::term, this));
}

Node* Parser::bind_op(TokenType type1, TokenType type2, std::function<Node* ()> func) {
	Node* left = func(); // First node
	
	while(cur_token.get_type() == type1 || cur_token.get_type() == type2) {
		Token opToken = cur_token; // Grab OP token
		advance(); // Advance to get "right" token
		Node* right = func();
		left = new Node(opToken, left, right);
	}

	return left; // Return first node or new Node
}

