#include "../headers/interpreter.hpp"
#include "../headers/token.hpp"

#include <iostream>
#include <stdexcept>
#include <string>


// To add it as Int or Double
// #define TOKEN_VALUE(token) \
// 	(token.get_raw_value().is_int) \
// 		? static_cast<int>(token.get_value()) \
// 		: static_cast<double>(token.get_value())


Interpreter::Interpreter() {}

Number* Interpreter::visit(Node* node) {
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


Number* Interpreter::visit_number(Node* node) {
	return new Number(node->get_token().get_value());
}

Number* Interpreter::visit_binary(Node* node) {
	// std::cout << "Found Binary" << std::endl;
	Number* left = visit(node->get_left());
	Number* right = visit(node->get_right());

	return left->eval(right->get_value(), node->get_token().get_type()) // Value, type of evaluation (add, minus etc)
			->set_pos(node->get_pos()); // Set position
}


Number* Interpreter::visit_unary(Node* node) {
	// std::cout << "Found Unary" << std::endl;
	Number* number = visit(node->get_child());

	// -1 because -> --X = X
	if(node->get_token().get_type() == TokenType::MINUS)
		number = number->eval(-1, TokenType::MUL);

	return number->set_pos(node->get_pos());
}
