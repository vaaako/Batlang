#pragma once

#include "nodes.hpp"
#include "number.hpp"
#include "result.hpp"

/**
 * This class assembles everything from Lexer and Parser to print a result of all
 * 
 * The nodes start at visit, depending of the type, one of the other visit are executed, interpreted and returns a result
 * */

class Interpreter {
	public:
		Interpreter();

		RTResult visit(Node* node);
		RTResult visit_number(Node* node);
		RTResult visit_binary(Node* node);
		RTResult visit_unary(Node* node);
	private:
};