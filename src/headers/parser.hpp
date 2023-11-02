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
		Parser(const std::vector<Token> tokens);

		inline void advance() {
			// if(++token_index < tokens.size())
				// cur_token = pop();
				// cur_token = tokens.at(token_index);
			if(tokens.size() != 0) cur_token = pop_token();
		}

		inline Result parse() {
			Result res = expr(); // MUL and DIV priority

			// Not reach the end of file
			if(!res.has_error() && cur_token.get_type() != TokenType::TEOF) {
				return res.set_error(
					Error(ErrorType::InvalidSyntaxError,
						  cur_token.get_pos(),
						  "Expected some operator"
						)
					);
			}

			return res;
		}


		Result factor();
		Result term();
		Result expr();

		// Node* bind_op(TokenType type1, TokenType type2, Node* (*func)());
		Result bind_op(const TokenType type1, const TokenType type2, const std::function<Result ()> func);
	private:
		std::vector<Token> tokens;
		// Token cur_token = tokens.at(0);
		Token cur_token = pop_token();

		std::optional<Error> error;

		// size_t token_index = 0;

		// Just a shortcut
		inline bool has_types(const TokenType to_check, const TokenType type1, const TokenType type2) const {
			return to_check == type1 || to_check == type2;
		}

		inline Token pop_token() {
			Token token = tokens.at(0);
			tokens.erase(tokens.begin());
			return token;
		}
};


