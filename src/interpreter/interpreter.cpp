#include "../headers/interpreter.hpp"
#include "../headers/token.hpp"
#include "../headers/result.hpp"

#include <iostream>
#include <stdexcept>
#include <string>


// To add it as Int or Double
// #define TOKEN_VALUE(token) \
// 	(token.get_raw_value().is_int) \
// 		? static_cast<int>(token.get_value()) \
// 		: static_cast<double>(token.get_value())


Interpreter::Interpreter() {}

RTResult Interpreter::visit(Node* node) {
	switch (node->get_type()) {
		case NodeType::NUMBER:
			return visit_number(node);
		case NodeType::BINARY:
			return visit_binary(node);
		case NodeType::UNARY:
			return visit_unary(node);
		default:
			throw std::runtime_error("No visit method found for " + Node::get_type_as_string(node->get_type()));
			break;
	}
}


RTResult Interpreter::visit_number(Node* node) {
	RTResult res = RTResult();
	res.sucess(Number(node->get_token().get_value()));
	return res;
}

RTResult Interpreter::visit_binary(Node* node) {
	// std::cout << "Found Binary" << std::endl;
	RTResult res = RTResult();

	// Get numbers
	Number left = visit(node->get_left()).get_value();
	Number right = visit(node->get_right()).get_value();

	// Eval
	EvalResult result = left.eval(right.get_value(), node->get_token().get_type(), node->get_pos()); // Value, type of evaluation (add, minus etc)
	
	// Check for error
	if(result.has_error()) {
		res.failure(result.get_error());
		return res;
	}

	// Sucess
	res.sucess(
		Number(result.get_value()).set_pos(node->get_pos()) // Make a number type with the result
	);

	return res;
}


RTResult Interpreter::visit_unary(Node* node) {
	// std::cout << "Found Unary" << std::endl;
	RTResult res = RTResult();

	RTResult number = res.registr(visit(node->get_child()));
	if(res.has_error()) res.failure(number.get_error()); // Check error from visit

	// Eval
	EvalResult result = 0;
	if(node->get_token().get_type() == TokenType::MINUS)
		// -1 because -> --X = +X
		result = number.get_value().eval(-1, TokenType::MUL, node->get_pos());

	// Check result error
	if(result.has_error()) {
		res.failure(result.get_error());
		return res;
	}

	// Sucess
	res.sucess(
		Number(
			(result.get_value() == 0) ? number.get_value() : result.get_value() // Get value of initial number or the result from eval (if has)
		).set_pos(node->get_pos())
	); // Change initial value
	return number;
}
