#include "../headers/interpreter.hpp"
#include "../headers/token.hpp"
#include "../headers/result.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>


// To add it as Int or Double
// #define TOKEN_VALUE(token) \
// 	(token.get_raw_value().is_int) \
// 		? static_cast<int>(token.get_value()) \
// 		: static_cast<double>(token.get_value())


Interpreter::Interpreter(Context& context) : context(context) {}

RTResult Interpreter::visit(const Node& node) {
	switch (node.get_type()) {
		case NodeType::NUMBER:
			return visit_number(node);
		case NodeType::BINARY:
			return visit_binary(node);
		case NodeType::UNARY:
			return visit_unary(node);
		default:
			throw std::runtime_error("No visit method found for " + Node::get_type_as_string(node.get_type()));
			break;
	}
}


RTResult Interpreter::visit_number(const Node& node) {
	RTResult res = RTResult();

	// Make number and set context
	res.sucess(
		Number(node.get_token().get_value(), context)
	);
	return res;
}

RTResult Interpreter::visit_binary(const Node& node) {
	// std::cout << "Found Binary" << std::endl;
	RTResult res = RTResult();

	// Get numbers (don't need to register because there is no way of getting a error)
	Number left = visit(node.get_left()).get_value();
	Number right = visit(node.get_right()).get_value();

	// Eval
	EvalResult result = left.eval(right.get_value(), node.get_token().get_type(), node.get_pos()); // Value, type of evaluation (add, minus etc)
	
	// Check for error
	if(result.has_error()) {
		res.failure(result.get_error());
		return res;
	}

	// Sucess
	res.sucess(Number(
		result.get_value(), // Make a number type with the result
		node.get_pos(),
		context
	));

	return res;
}


RTResult Interpreter::visit_unary(const Node& node) {
	// std::cout << "Found Unary" << std::endl;
	RTResult res = RTResult();
	RTResult number = res.registr(visit(node.get_child()));
	if(res.has_error()) res.failure(number.get_error()); // Check error from visit

	// Eval
	EvalResult result = 0; // I'm just using EvalResult and not RTResult to avoid circular import
	if(node.get_token().get_type() == TokenType::MINUS)
		// -1 because -> --X = +X
		result = number.get_value().eval(-1, TokenType::MUL, node.get_pos());

	// Check result error
	if(result.has_error()) {
		res.failure(result.get_error());
		return res;
	}

	// Sucess	
	res.sucess(Number(
		(result.get_value() == 0) ? number.get_value().get_value() : result.get_value(), // Get value of initial number or the result from eval (if has)
		node.get_pos(),
		context
	)); // Change initial value

	return res;
}
