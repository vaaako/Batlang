#pragma once

#include "nodes.hpp"
#include "number.hpp"

/**
 * This class assembles everything from Lexer and Parser to print a result of all
 * 
 * The nodes start at visit, depending of the type, one of the other visit are executed, interpreted and returns a result
 * */

class Interpreter {
	public:
		Interpreter();

		Number visit(Node* node);
		Number visit_number(Node* node);
		Number visit_binary(Node* node);
		Number visit_unary(Node* node);
	private:
};