#include "../headers/interpreter.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

Interpreter::Interpreter() {}


void Interpreter::visit(NodeType node_type) {
	switch (node_type) {
		case NodeType::NUMBER:
			return visit_number();
			break;
		case NodeType::BINARY:
			return visit_binary();
			break;
		case NodeType::UNARY:
			return visit_unary();
			break;
		default:
			throw std::runtime_error("No visit method found for " + Node::get_type_as_string(node_type));
			break;
	}
}


void Interpreter::visit_number() {
	std::cout << "Found Number" << std::endl;
}

void Interpreter::visit_binary() {
	std::cout << "Found Binary" << std::endl;
}

void Interpreter::visit_unary() {
	std::cout << "Found Unary" << std::endl;
}
