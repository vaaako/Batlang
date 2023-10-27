#pragma once

#include "token.hpp"
#include "nodes.hpp"

#include <cstddef>
#include <optional>
#include <vector>
#include <functional>

class Parser {
	public:
		Parser(std::vector<Token> tokens);

		void advance();
		Node* parse(); // BinOpNode

		Node* factor();
		Node* term(); // BinOpNode
		Node* expr(); // BinOpNode
	private:
		std::vector<Token> tokens;
		Token cur_token = tokens[0];

		size_t token_index = 0;
};