#pragma once

#include "error.hpp"
#include "result.hpp"
#include "token.hpp"
#include "nodes.hpp"

#include <optional>
#include <vector>
#include <functional>

class Parser {
	public:
		Parser(std::vector<Token> tokens);

		void advance();
		Result parse();

		Result factor();

		Result term();
		Result expr();



		// Node* bind_op(TokenType type1, TokenType type2, Node* (*func)());
		Result bind_op(TokenType type1, TokenType type2, std::function<Result ()> func);
	private:
		std::vector<Token> tokens;
		Token cur_token = tokens[0];

		std::optional<Error> error;

		size_t token_index = 0;


		// Just a shortcut
		bool has_types(TokenType to_check, TokenType type1, TokenType type2);
};


