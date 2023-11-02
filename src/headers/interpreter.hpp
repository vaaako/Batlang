#pragma once

#include "nodes.hpp"
#include "number.hpp"

class Interpreter {
	public:
		Interpreter();

		Number* visit(Node* node);
		Number* visit_number(Node* node);
		Number* visit_binary(Node* node);
		Number* visit_unary(Node* node);
	private:
};