#pragma once

#include "error.hpp"
#include "result.hpp"
#include "token.hpp"
#include "node.hpp"

#include <optional>
#include <vector>
#include <functional>

/**
 * This is the parser
 * It works with the "result" class to handle erros
 * 
 * With the tokens from the "lexer" it checks if it's "in order"
 * 
 * REMEMBER: On setting a new Node, remember to check if node is NUMBER, UNARY or BINARY if none of that, you need to set manually,
 * example: new Node(token, left_node, nullptr, NodeType::VARIABLE)
 * */

class Parser {
	public:
		Parser(const std::vector<Token>& tokens);

		inline void advance() {
			if(tokens.size() != 0) cur_token = pop_token();
		}

		inline PResult parse() {
			PResult res = expr(); // MUL and DIV priority

			// Not reach the end of file
			if(!res.has_error() && cur_token.get_type() != TokenType::TEOF) {
				// Register error
				res.failure(
					Error(ErrorType::InvalidSyntaxError,
						  "Expected some operator, but got '" + cur_token.value_as_string() + "'",
						  cur_token.get_pos()
						)
					);
			}

			// Return result
			return res;
		}



		// Node* bind_op(TokenType type1, TokenType type2, Node* (*func)());
		// PResult bind_op(const TokenType type1, const TokenType type2, const std::function<PResult ()> func);
		PResult bind_op(const TokenType type1, const TokenType type2, const std::function<PResult ()> func, const std::function<PResult ()> func2 = nullptr);
	private:
		std::vector<Token> tokens;
		Token cur_token = pop_token();

		std::optional<Error> error;

		PResult atom();
		PResult factor();

		PResult power();
		PResult term();
		PResult expr();

		// Just a shortcut
		inline bool has_types(const TokenType to_check, const TokenType type1, const TokenType type2) const {
			return to_check == type1 || to_check == type2;
		}

		// Poping instead of just query
		inline Token pop_token() {
			Token token = tokens.at(0);
			tokens.erase(tokens.begin());
			return token;
		}
};


