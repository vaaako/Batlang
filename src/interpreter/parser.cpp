#include "../headers/parser.hpp"

#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

/* Privates */

// Power
PResult Parser::atom() {
	PResult res = PResult();
	Token token = cur_token;

	advance();
	// res.registr(cur_token);

	// Number //
	if(has_types(token.get_type(), TokenType::INT, TokenType::FLOAT)) {
		res.sucess(new Node(token)); // Sucess
		return res;

	// Variable //
	// } else if(token.get_type() == TokenType::IDENTIFIER) {
	// 	// res.sucess(new Node(token, nullptr, nullptr, NodeType::ACESS)); // Var Acess
	// 	res.sucess(new Node(token)); // Var Acess
	// 	return res;

	// Parentheses //
	}  else if(token.get_type() == TokenType::LPARENT) {
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

PResult Parser::factor() {
	PResult res = PResult();
	Token token = cur_token;
	
	// +X or -X //
	if(has_types(token.get_type(), TokenType::PLUS, TokenType::MINUS)) {
		advance();
		// res.registr(cur_token);

		// Get unary factor
		PResult factor = res.registr(this->factor());
		if(factor.has_error()) return res;

		// Sucess
		res.sucess(new Node(token, factor.get_value()));
		return res;
	}

	// Check for power
	return power(); // This is necessary because POWER has more priority than MUL and DIV
}


PResult Parser::power() {
	return bind_op(TokenType::POW, TokenType::UNKNOWN, std::bind(&Parser::atom, this), std::bind(&Parser::factor, this)); // Calc atom and factor
}

// BinOpNode
PResult Parser::term() {
	return bind_op(TokenType::MUL, TokenType::DIV, std::bind(&Parser::factor, this));
}

// BinOpNode
PResult Parser::expr() {
	PResult res = PResult();

	// If is a var declaration, get KEYWORD, IDENTIFIER, EQ and expr
	if(cur_token.get_type() == TokenType::KEYWORD && cur_token.get_value() == "let") {
		advance();
		// res.registr();

		// Check for var name
		if(cur_token.get_type() != TokenType::IDENTIFIER) {
			res.failure(Error(ErrorType::InvalidSyntaxError,
			  		  "Expected variable name, but got '" + cur_token.value_as_string() + "'",
			  		  cur_token.get_pos())
					);
			return res;
		}

		Token var_name = cur_token;

		advance();
		// res.registr();

		// Check for '='
		if(cur_token.get_type() != TokenType::EQUALS) {
			res.failure(Error(ErrorType::InvalidSyntaxError,
			  		  "Expected '=', but got '" + cur_token.value_as_string() + "'",
			  		  cur_token.get_pos())
					);
			return res;
		}

		advance();
		// res.registr();

		PResult expr = res.registr(this->expr());
		if(expr.has_error()) return res;

		// return res.sucess(new Node(var_name, expr));
		res.sucess(new Node(var_name, expr.get_value(), nullptr, NodeType::VARIABLE));
		return res;
	}


	return bind_op(TokenType::PLUS, TokenType::MINUS, std::bind(&Parser::term, this));
}

PResult Parser::bind_op(const TokenType type1, const TokenType type2, const std::function<PResult ()> func, const std::function<PResult ()> func2) {
	PResult res = PResult();

	PResult left = res.registr(func()); // First node
	if(res.has_error()) return res; // Check if revious function had a error and return early
	Node* node = left.get_value(); // Grab node

	while(cur_token.get_type() == type1 || cur_token.get_type() == type2) {
		Token opToken = cur_token; // Grab OP token
		advance(); // Advance to get "right" token
		// res.registr(cur_token);
		
		PResult right = res.registr((func2 == nullptr) ? func() : func2()); // Use "func" if "func2" is nullptr
		if(res.has_error()) return res; // Check if previous function had a error and return early

		node = new Node(opToken, node, right.get_value());
	}

	// Return first node or new Node
	res.sucess(node); // Sucess
	return res;
}


/*
lest -> highest priority

expr   : KEYWORD:VAR IDENTIFIER EQ expr
	   : term ((PLUS|MINUS) term)*
term   : factor ((MUL|DIV) factor)*
factor : (PLUS|MINUS) factor
	   : power
power  : atom (POW factor)*
atom   : INT|FLOAT|IDENTIFIER
	   : LPARENT expr RPARENT
*/
