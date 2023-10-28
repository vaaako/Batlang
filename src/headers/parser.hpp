#pragma once

#include "token.hpp"
#include "nodes.hpp"

#include <vector>
#include <functional>

class Parser {
	public:
		Parser(std::vector<Token> tokens);

		void advance();
		Node* parse(); // BinOpNode

		Node* factor(); // Node Number
		Node* term(); // BinOpNode
		Node* expr(); // BinOpNode

		// Node* bind_op(TokenType type1, TokenType type2, Node* (*func)());
		Node* bind_op(TokenType type1, TokenType type2, std::function<Node* ()> func);
	private:
		std::vector<Token> tokens;
		Token cur_token = tokens[0];

		size_t token_index = 0;
};