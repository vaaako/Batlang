#include "../headers/parser.hpp"

#include <iostream>

Parser::Parser(const std::vector<Token> tokens) : tokens(tokens) {}

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
		return res.sucess(new Node(token, factor.get_node()));


	// Number //
	} else if(has_types(token.get_type(), TokenType::INT, TokenType::FLOAT)) {
		advance();
		// res.registr(cur_token);

		return res.sucess(new Node(token)); // Sucess


	// Parentheses //
	} else if(token.get_type() == TokenType::LPARENT) {
		advance();
		// res.registr(cur_token);

		// Get Parentheses expression
		Result expr = res.registr(this->expr());
		if(expr.has_error()) return res;

		// Check if closed
		if(cur_token.get_type() == TokenType::RPARENT) {
			advance();
			// res.registr(cur_token);

			return res.sucess(expr.get_node()); // Sucess
		} else {
			return res.failure(
				Error(ErrorType::InvalidSyntaxError,
					  cur_token.get_pos(),
					  "Expected ')'"
				)
			);
		}
	}



	// Don't start with a valid token, "Throw" error
	return res.failure(
		Error(ErrorType::InvalidSyntaxError,
			  token.get_pos(),
			  "Expected <INT>, <FLOAT> or '(' type, but got '" + token.value_as_string() + "'"
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

Result Parser::bind_op(const TokenType type1, const TokenType type2, const std::function<Result ()> func) {
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
	return res.sucess(node); // Sucess
}


/* Privates */



/*
expr   : term ((PLUS|MINUS) term)*
term   : factor ((MUL|DIV) factor)*
factor : INT|FLOAT
	   : (PLUS|MINUS) factor
	   : LPARENT expr RPARENT
*/
