#include "../headers/parser.hpp"
#include "../headers/error.hpp"
#include "../headers/result.hpp"

#include <iostream>

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {}

void Parser::advance() {
	if(++token_index < tokens.size())
		cur_token = tokens[token_index];
}

Result Parser::parse() {
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

Result Parser::factor() {
	Result res = Result();
	Token token = cur_token;
	
	// +X or -X //
	if(has_types(token.get_type(), TokenType::PLUS, TokenType::MINUS)) {
		advance();
		// res.registr(cur_token);

		// Get unary factor
		Result factor = res.registr(this->factor());
		if(factor.has_error()) return res;

		// Sucess
		return res.set_node(new Node(token, factor.get_node()));


	// Number //
	} else if(has_types(token.get_type(), TokenType::INT, TokenType::FLOAT)) {
		advance();
		// res.registr(cur_token);

		return res.set_node(new Node(token)); // Sucess


	// Parentheses //
	} else if(token.get_type() == TokenType::LPARENT) {
		advance();
		// res.registr(cur_token);

		// Get Parentheses expression
		Result expr = res.registr(this->expr());
		if(expr.has_error()) return res;

		if(cur_token.get_type() == TokenType::RPARENT) {
			advance();
			// res.registr(cur_token);

			return res.set_node(expr.get_node()); // Sucess
		} else {
			return res.set_error(
				Error(ErrorType::InvalidSyntaxError,
					  cur_token.get_pos(),
					  "Expected ')'"
				)
			);
		}
	}



	// Don't start with a valid token, "Throw" error
	return res.set_error(
		Error(ErrorType::InvalidSyntaxError,
			  token.get_pos(),
			  "Expected INT or FLOAT Type, got '" + token.get_value() + "'"
			)
		);
}


// BinOpNode
Result Parser::term() {
	return bind_op(TokenType::MUL, TokenType::DIV, std::bind(&Parser::factor, this));
}

// BinOpNode
Result Parser::expr() {
	return bind_op(TokenType::PLUS, TokenType::MINUS, std::bind(&Parser::term, this));
}

Result Parser::bind_op(TokenType type1, TokenType type2, std::function<Result ()> func) {
	Result res = Result();

	Result left = res.registr(func()); // First node
	if(res.has_error()) return res; // Check if revious function had a error
	Node* node = left.get_node(); // Grab node

	while(cur_token.get_type() == type1 || cur_token.get_type() == type2) {
		Token opToken = cur_token; // Grab OP token
		advance(); // Advance to get "right" token
		// res.registr(cur_token);
		
		Result right = res.registr(func());
		if(res.has_error()) return res; // Check if revious function had a error

		node = new Node(opToken, node, right.get_node());
	}

	// Return first node or new Node
	return res.set_node(node); // Sucess
}


/* Privates */
bool Parser::has_types(TokenType to_check, TokenType type1, TokenType type2) {
	return to_check == type1 || to_check == type2;
}


/*
expr   : term ((PLUS|MINUS) term)*
term   : factor ((MUL|DIV) factor)*
factor : INT|FLOAT
	   : (PLUS|MINUS) factor
	   : LPARENT expr RPARENT
*/
