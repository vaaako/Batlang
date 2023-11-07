#include "../headers/parser.hpp"

#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

PResult Parser::factor() {
	PResult res = PResult();
	Token token = cur_token;

	advance();
	// res.registr(cur_token);

	/**
	 * I am almost sure there is a best way of doing this withou this IFs and ELSEs, and just dont know how
	 * */
	
	// Number //
	if(has_types(token.get_type(), TokenType::INT, TokenType::FLOAT)) {
		res.sucess(new Node(token)); // Sucess
		return res;


	// +X or -X //
	} else if(has_types(token.get_type(), TokenType::PLUS, TokenType::MINUS)) {
		// Get unary factor
		PResult factor = res.registr(this->factor());
		if(factor.has_error()) return res;

		// Sucess
		res.sucess(new Node(token, factor.get_value()));
		return res;


	// Parentheses //
	} else if(token.get_type() == TokenType::LPARENT) {
		// Get Parentheses expression
		PResult expr = res.registr(this->expr());
		if(expr.has_error()) return res;

		// Check if closed
		if(cur_token.get_type() == TokenType::RPARENT) {
			advance();
			// res.registr(cur_token);

			res.sucess(expr.get_value()); // Sucess
			return res;
		}

		res.failure(
			Error(ErrorType::InvalidSyntaxError,
				  "Expected ')', but got '" + cur_token.value_as_string() + "'",
				  cur_token.get_pos()
			)
		);
		return res;
	}



	// Don't start with a valid token, "Throw" error
	res.failure(
		Error(ErrorType::InvalidSyntaxError,
			  "Expected <INT>, <FLOAT> or '(' type, but got '" + token.value_as_string() + "'",
			  token.get_pos()
			)
		);
	return res;
}


// BinOpNode
PResult Parser::term() {
	return bind_op(TokenType::MUL, TokenType::DIV, std::bind(&Parser::factor, this));
}

// BinOpNode
PResult Parser::expr() {
	return bind_op(TokenType::PLUS, TokenType::MINUS, std::bind(&Parser::term, this));
}

PResult Parser::bind_op(const TokenType type1, const TokenType type2, const std::function<PResult ()> func) {
	PResult res = PResult();

	PResult left = res.registr(func()); // First node
	if(res.has_error()) return res; // Check if revious function had a error and return early
	Node* node = left.get_value(); // Grab node

	while(cur_token.get_type() == type1 || cur_token.get_type() == type2) {
		Token opToken = cur_token; // Grab OP token
		advance(); // Advance to get "right" token
		// res.registr(cur_token);
		
		PResult right = res.registr(func());
		if(res.has_error()) return res; // Check if previous function had a error and return early

		node = new Node(opToken, node, right.get_value());
	}

	// Return first node or new Node
	res.sucess(node); // Sucess
	return res;
}


/* Privates */



/*
expr   : term ((PLUS|MINUS) term)*
term   : factor ((MUL|DIV) factor)*
factor : INT|FLOAT
	   : (PLUS|MINUS) factor
	   : LPARENT expr RPARENT
*/
